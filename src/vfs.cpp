#include "vfs.hpp"
#include "binaryReader.cpp"
#include "binaryReader.hpp"
#include "box.hpp"
#include "utils.cpp"
#include "crc.cpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>

#ifndef __has_include
  static_assert(false, "__has_include not supported");
#else
#  if __cplusplus >= 201703L && __has_include(<filesystem>)
#    include <filesystem>
     namespace fs = std::filesystem;
#  elif __has_include(<experimental/filesystem>)
#    include <experimental/filesystem>
     namespace fs = std::experimental::filesystem;
#  elif __has_include(<boost/filesystem.hpp>)
#    include <boost/filesystem.hpp>
     namespace fs = boost::filesystem;
#  endif
#endif

using svec= std::vector<std::string>;
using bvec= std::vector<uint8_t>;
using lvec= std::vector<uint32_t>;

#define strc std::to_string

std::string executeCommand(std::string command) {
  std::string output = "";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "Error: failed to execute command.";
    }
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        output += buffer;
    }
    pclose(pipe);
    return output;
}

short VFSreunpack::methodType(FileBuffer file)
{
  // 0 -> Unknown
  // 1 -> XBB
  // 2 -> ANA

  file.set(0);
  if (file.getb() == 0x58)
  {file.set(1); if (file.getb() == 0x42) {file.set(2); if (file.getb() == 0x42) {return 1;}}}
  
  file.set(0);
  if (file.getb() == 0x40)
  {file.set(1); if (file.getb() == 0x41) {file.set(2); if (file.getb() == 0x4E) {file.set(3); if (file.getb() == 0x41) {return 2;}}}}

  return 0;
}

void VFSreunpack::filesXBB(FileBuffer file)
{
  std::vector<std::string> filenames;

  //this new amazing technology allows you to work with binary data easier than ever
  //sponsored by the nerdz and cute catgirrrs :3
  binReader reader(file.getd());

  //set pointer to 4 to pass the XBB header and magic flag 4
  reader.s(4); //4 means fifth value since arrays start at 0

  //get file count
  int fileCount= reader.read();
  debug("[VFSreunpack::filesXBB] file count: "+std::to_string(fileCount));

  reader.s(0x20); //seek beyond header
  reader.i((4+4+4)*fileCount); //skip pointers
  reader.i(4*fileCount); //skip CRC32
  reader.i(8*fileCount); //skip metablob

  for (int i= 0; i < fileCount; i++)
  {
    std::vector<uint8_t> dirtyFileName;
    while (true)
    {
      uint8_t rb= reader.read();
      if (rb == 0x0) {break;}
      dirtyFileName.push_back(rb);
    }
    uint8_t* slightlyLessDirtyFileName= new uint8_t[dirtyFileName.size()];
    for (size_t i= 0; i < dirtyFileName.size(); i++)
    {
      slightlyLessDirtyFileName[i]= dirtyFileName[i];
    }
    debug("[VFSreunpack::filesXBB] filename delivered: "+uc2s(slightlyLessDirtyFileName));
    filenames.push_back(uc2s(slightlyLessDirtyFileName));
  }

  //print info
  CLIcontainer box("Initial D VFS tools", 36);
  box.setf("file count: "+std::to_string(fileCount));
  box.seto("files");
  box.setb(filenames);
  box.render();
  
}

void VFSreunpack::infoXBB(FileBuffer file)
{
  // initialize the binary reader
  binReader reader(file.getd());

  //skip header
  reader.s(3);
  //read MF4
  uint8_t mf4= reader.read();
  //read file count
  size_t fc= reader.read();
  //seek to header and beyond
  reader.s(0x20);

  //reading part
  
  //initialize some vectors to store data
  svec filenames;
  lvec ptr_s;
  lvec ptr_e;
  lvec ptr_f;
  lvec crc;

  //get start and end pointers
  for (size_t i= 0; i < fc; i++)
  {
    //get start pointer
    uint8_t* sbuffer= reader.read(4);
    uint32_t startPTR= sbuffer[0] | (sbuffer[1] << 8) | (sbuffer[2] << 16) | (sbuffer[3] << 24);
    debug("[VFSreunpack::infoXBB] start ptr at: "+l2h(startPTR)+" => "+std::to_string(startPTR));
    //get end pointer
    uint8_t* ebuffer= reader.read(4);
    uint32_t endPTR= ebuffer[0] | (ebuffer[1] << 8) | (ebuffer[2] << 16) | (ebuffer[3] << 24);
    debug("[VFSreunpack::infoXBB] end ptr at: "+l2h(endPTR)+" => "+std::to_string(endPTR));
    //get file pointer
    uint8_t* fbuffer= reader.read(4);
    uint32_t filePTR= fbuffer[0] | (fbuffer[1] << 8) | (fbuffer[2] << 16) | (fbuffer[3] << 24);
    debug("[VFSreunpack::infoXBB] file ptr at: "+l2h(filePTR)+" => "+std::to_string(filePTR));
    //get file pointer
    uint8_t* hbuffer= reader.read(4);
    uint32_t hash= hbuffer[0] | (hbuffer[1] << 8) | (hbuffer[2] << 16) | (hbuffer[3] << 24);
    debug("[VFSreunpack::infoXBB] original CRC32 hash: "+l2h(hash)+" => "+std::to_string(hash));

    ptr_s.push_back(startPTR);
    ptr_e.push_back(endPTR);
    ptr_f.push_back(filePTR);
    crc.push_back(hash);
  }
  
  //the dirty filename sift
  for (int i= 0; i < fc; i++)
  {
    reader.s(ptr_f[i]);
    std::vector<uint8_t> dirtyFileName;
    while (true)
    {
      uint8_t rb= reader.read();
      if (rb == 0x0) {break;}
      dirtyFileName.push_back(rb);
    }
    uint8_t* slightlyLessDirtyFileName= new uint8_t[dirtyFileName.size()];
    for (size_t i= 0; i < dirtyFileName.size(); i++)
    {
      slightlyLessDirtyFileName[i]= dirtyFileName[i];
    }
    debug("[VFSreunpack::infoXBB] filename delivered: "+uc2s(slightlyLessDirtyFileName));
    filenames.push_back(uc2s(slightlyLessDirtyFileName));
  }

  //set data for each struct
  std::vector<XBBstruct> packs;
  for (size_t i= 0; i < fc; i++)
  {
    // create a new XBB file struct
    XBBstruct pack;

    pack.index= i;
    pack.PTRstart= ptr_s[i];
    pack.PTRend= ptr_e[i];
    pack.PTRfname= ptr_f[i];
    pack.crc32= crc[i];
    pack.fileName= filenames[i];

    packs.push_back(pack);
  }

  //display
  CLIcontainer box("Initial D VFS Tools", 36);
  box.seto("info");
  box.setf("file count: "+std::to_string(fc));
  svec boxb;
  for (size_t i= 0; i < int(fc); i++)
  {
    CRC32 crack;
    uint8_t* cruffer= new uint8_t[packs[i].data.size()];
    std::copy(packs[i].data.begin(), packs[i].data.end(), cruffer);
    crack.Update(cruffer, packs[i].data.size());
    uint32_t crchash= crack.GetValue();
    
    boxb.push_back(packs[i].fileName);
    boxb.push_back((packs[i].fileName.length()*str("~")) );
    boxb.push_back("[index]                 ["+strc(packs[i].index + 1)+"/"+strc(fc)+"]");
    boxb.push_back("[start pointer]         "+l2h(packs[i].PTRstart));
    boxb.push_back("[end pointer]           "+l2h(packs[i].PTRend));
    boxb.push_back("[filename pointer]      "+l2h(packs[i].PTRfname));
    boxb.push_back("[CRC32]                 "+l2h(packs[i].crc32));
    boxb.push_back("[custom CRC]            "+l2h(crchash));

    if (i < (fc - 1)) {boxb.push_back("<BOX::SEP>");}
  }
  box.setb(boxb);
  box.render();
}

void VFSreunpack::extractXBB(FileBuffer file)
{
  // initialize the binary reader
  binReader reader(file.getd());

  //skip header
  reader.s(3);
  //read MF4
  uint8_t mf4= reader.read();
  //read file count
  size_t fc= reader.read();
  //seek to header and beyond
  reader.s(0x20);

  //reading part
  
  //initialize some vectors to store data
  svec filenames;
  lvec ptr_s;
  lvec ptr_e;
  lvec ptr_f;
  lvec crc;

  //get start and end pointers
  for (size_t i= 0; i < fc; i++)
  {
    //get start pointer
    uint8_t* sbuffer= reader.read(4);
    uint32_t startPTR= sbuffer[0] | (sbuffer[1] << 8) | (sbuffer[2] << 16) | (sbuffer[3] << 24);
    debug("[VFSreunpack::infoXBB] start ptr at: "+l2h(startPTR)+" => "+std::to_string(startPTR));
    //get end pointer
    uint8_t* ebuffer= reader.read(4);
    uint32_t endPTR= ebuffer[0] | (ebuffer[1] << 8) | (ebuffer[2] << 16) | (ebuffer[3] << 24);
    debug("[VFSreunpack::infoXBB] end ptr at: "+l2h(endPTR)+" => "+std::to_string(endPTR));
    //get file pointer
    uint8_t* fbuffer= reader.read(4);
    uint32_t filePTR= fbuffer[0] | (fbuffer[1] << 8) | (fbuffer[2] << 16) | (fbuffer[3] << 24);
    debug("[VFSreunpack::infoXBB] file ptr at: "+l2h(filePTR)+" => "+std::to_string(filePTR));
    //get file pointer
    uint8_t* hbuffer= reader.read(4);
    uint32_t hash= hbuffer[0] | (hbuffer[1] << 8) | (hbuffer[2] << 16) | (hbuffer[3] << 24);
    debug("[VFSreunpack::infoXBB] original CRC32 hash: "+l2h(hash)+" => "+std::to_string(hash));

    ptr_s.push_back(startPTR);
    ptr_e.push_back(endPTR);
    ptr_f.push_back(filePTR);
    crc.push_back(hash);
  }
  
  //the dirty filename sift
  for (int i= 0; i < fc; i++)
  {
    reader.s(ptr_f[i]);
    std::vector<uint8_t> dirtyFileName;
    while (true)
    {
      uint8_t rb= reader.read();
      if (rb == 0x0) {break;}
      dirtyFileName.push_back(rb);
    }
    uint8_t* slightlyLessDirtyFileName= new uint8_t[dirtyFileName.size()];
    for (size_t i= 0; i < dirtyFileName.size(); i++)
    {
      slightlyLessDirtyFileName[i]= dirtyFileName[i];
    }
    std::string fn= uc2s(slightlyLessDirtyFileName);

    //fix absurd bug causing buffers that shouldnt even run to merge with the filename
    //ps: this fix limits extension lenths to 3, including hard limiting it (in case the ext is 2 chars long)
    int dotLocation= fn.rfind('.', fn.npos);
    std::string cleanFN= "";
    for (int i= 0; i < (dotLocation + 4); i++)
    {cleanFN += fn[i];}
    fn= cleanFN;

    debug("[VFSreunpack::infoXBB] filename delivered: "+fn);
    filenames.push_back(fn);
  }

  //set data for each struct
  std::vector<XBBstruct> packs;
  for (size_t i= 0; i < fc; i++)
  {
    // create a new XBB file struct
    XBBstruct pack;

    pack.index= i;
    pack.PTRstart= ptr_s[i];
    pack.PTRend= ptr_e[i];
    pack.PTRfname= ptr_f[i];
    pack.crc32= crc[i];
    pack.fileName= filenames[i];

    packs.push_back(pack);
  }
  
  #ifdef _WIN32
    executeCommand("mkdir EXTRACTED");
    executeCommand("mkdir EXTRACTED/"+file.filename_no_ext);
  #else
    fs::create_directory("./EXTRACTED");
    fs::create_directory("./EXTRACTED/"+file.filename_no_ext);
  #endif

  for (size_t i= 0; i < fc; i++)
  {
    uint32_t fileStart= packs[i].PTRstart;
    uint32_t toRead= packs[i].PTRend;
    str filename= filenames[i];
    
    reader.s(fileStart);
    while (true)
    {
      if (toRead <= 0) {break;}
      toRead--; packs[i].data.push_back(reader.read());
    }
    save2file(packs[i].data, "./EXTRACTED/"+file.filename_no_ext+"/"+filename);
    sprint("Extracted file: ./EXTRACTED/"+file.filename_no_ext+"/"+filename);
    debug("[VFSreunpack::extractXBB] {"+l2h(packs[i].PTRstart)+" -> "+l2h(packs[i].PTRstart+packs[i].PTRend)+"} => "+filename);
  }
}

void VFSreunpack::filesANA(FileBuffer file)
{
  binReader reader(file.getd());

  CLIcontainer box("Initial D VFS tools", 36);
  box.seto("files");

  reader.s(0x10);
  uint8_t fc= reader.read();
  reader.s(0x20);

  vec filenames;

  for (int i= 0; i < fc; i++)
  {
    uint8_t* fb_ptr= reader.read(4);
    uint8_t* fr_ptr= reader.read(4);

    std::vector<uint8_t> fnb;
    while (1)
    {
      uint8_t rb= reader.read();
      if (rb == 0x0) {break;}
      fnb.push_back(rb);
    }
    uint8_t* fnameinunint8= new uint8_t[fnb.size()];
    for (int i= 0; i < fnb.size(); i++)
    {fnameinunint8[i]= fnb[i];}
    filenames.push_back(uc2s(fnameinunint8));
  }

  box.setf("file count: "+to_string(fc));
  box.setb(filenames);
  box.render();
}

void VFSreunpack::infoANA(FileBuffer file)
{
  binReader reader(file.getd());
  CLIcontainer box("Initial D VFS tools", 36);
  box.seto("info");

  //file count
  reader.s(0x10);
  uint8_t fc= reader.read();

  //skip header
  reader.s(0x20);

  //list of ANA files
  std::vector<ANAstruct> ANAfiles;

  //box contents
  vector<std::string> writeBody;

  for (size_t i= 0; i < fc; i++)
  {
    ANAstruct file;
    file.index= i+1;
    file.PTRstart= ( (reader.read()) | (reader.read() << 8) | (reader.read() << 16) | (reader.read() << 24) );
    file.PTRend= ( (reader.read()) | (reader.read() << 8) | (reader.read() << 16) | (reader.read() << 24) );

    vector<uint8_t> getFileName;
    while (1)
    {
      uint8_t rb= reader.read();
      if (rb == 0x0) {break;}
      getFileName.push_back(rb);
    }
    uint8_t* fileNameArray= new uint8_t[getFileName.size()];
    for (size_t i= 0; i < getFileName.size(); i++)
    {fileNameArray[i]= getFileName[i];}
    file.filename= uc2s(fileNameArray);
    delete[] fileNameArray;

    ANAfiles.push_back(file);
  }

  for (ANAstruct ana : ANAfiles)
  {
    writeBody.push_back(ana.filename);
    writeBody.push_back(str("~") * ana.filename.length());
    writeBody.push_back("[index]                 ["+to_string(ana.index)+"/"+to_string(fc)+"]");
    writeBody.push_back("[start pointer]         "+l2h(ana.PTRstart));
    writeBody.push_back("[end pointer]           "+l2h(ana.PTRend));

    if (!(ana.index == fc))
    {writeBody.push_back("<BOX::SEP>");}
  }

  box.setb(writeBody);
  box.setf("file count: "+to_string(fc));
  box.render();
}

void VFSreunpack::extractANA(FileBuffer file)
{
  binReader reader(file.getd());

  //file count
  reader.s(0x10);
  uint8_t fc= reader.read();

  //skip header
  reader.s(0x20);

  //list of ANA files
  std::vector<ANAstruct> ANAfiles;

  //box contents
  vector<std::string> writeBody;

  for (size_t i= 0; i < fc; i++)
  {
    ANAstruct file;
    file.index= i+1;
    file.PTRstart= ( (reader.read()) | (reader.read() << 8) | (reader.read() << 16) | (reader.read() << 24) );
    file.PTRend= ( (reader.read()) | (reader.read() << 8) | (reader.read() << 16) | (reader.read() << 24) );

    vector<uint8_t> getFileName;
    while (1)
    {
      uint8_t rb= reader.read();
      if (rb == 0x0) {break;}
      getFileName.push_back(rb);
    }
    uint8_t* fileNameArray= new uint8_t[getFileName.size()];
    for (size_t i= 0; i < getFileName.size(); i++)
    {fileNameArray[i]= getFileName[i];}
    file.filename= uc2s(fileNameArray);
    delete[] fileNameArray;

    ANAfiles.push_back(file);
  }

  for (size_t i= 0; i < fc; i++)
  {
    reader.s(ANAfiles[i].PTRstart);
    uint32_t toRead= ANAfiles[i].PTRend;
    while (1)
    {ANAfiles[i].data.push_back(reader.read()); if (toRead == 0){break;}else{toRead--;}}
    debug("[VFSreunpack::extractANA] pushed data of size ("+to_string(ANAfiles[i].data.size())+") to file: "+ANAfiles[i].filename+" i:"+to_string(ANAfiles[i].index));
    debug("                          ptr end:"+l2h(ANAfiles[i].PTRend));
  }

  uint32_t ANTptr= ANAfiles[fc-1].PTRstart + ANAfiles[fc-1].PTRend;
  uint32_t ANTend= file.gets();

  //create directory
  #ifdef _WIN32
    executeCommand("mkdir EXTRACTED");
    executeCommand("mkdir EXTRACTED/"+file.filename_no_ext);
  #else
    fs::create_directory("./EXTRACTED");
    fs::create_directory("./EXTRACTED/"+file.filename_no_ext);
  #endif

  for (ANAstruct ana : ANAfiles)
  {
    std::string filename= "./EXTRACTED/" + file.filename_no_ext + "/" + ana.filename + "(" + to_string(ana.index) + ").GIM";
    save2file(ana.data, filename);
    sprint("Extracted file: "+filename);
    debug("[VFSreunpack::extractANA] {"+l2h(ana.PTRstart)+" -> "+l2h(ana.PTRstart+ana.PTRend)+"} ("+to_string(ana.data.size())+")bytes => "+filename);
  }
}
