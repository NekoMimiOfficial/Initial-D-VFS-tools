#include "vfs.hpp"
#include "binaryReader.cpp"
#include "binaryReader.hpp"
#include "box.hpp"
#include "utils.cpp"
#include "crc.cpp"
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

using svec= std::vector<std::string>;
using bvec= std::vector<uint8_t>;
using lvec= std::vector<uint32_t>;

#define strc std::to_string

bool checkXBB(FileBuffer file)
{
  file.set(0);
  uint8_t* check= new uint8_t[3];
  return (uc2s(file.getw()) == "XBB");
}

short VFSreunpack::methodType(FileBuffer file)
{
  // 0 -> Unknown
  // 1 -> XBB
  // 2 -> ANA

  FileBuffer vfs= file;
  vfs.set(0x00);
  uint8_t* header= vfs.getw();

  if (uc2s(header) == "XBB"){return 1;}

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

  std::filesystem::create_directory("./EXTRACTED");
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
    save2file(packs[i].data, "./EXTRACTED/"+filename);
    sprint("Extracted file: "+filename);
    debug("[VFSreunpack::extractXBB] {"+l2h(packs[i].PTRstart)+" -> "+l2h(packs[i].PTRstart+packs[i].PTRend)+"} => "+filename);
  }
}
