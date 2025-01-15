#include "vfs.hpp"
#include "binaryReader.cpp"
#include "binaryReader.hpp"
#include "utils.cpp"
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

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

  reader.s(30); //seek beyond header
  reader.i((4+4+4)*fileCount); //skip pointers
  reader.i(8*fileCount); //skip metablob
  reader.i(4*fileCount); //skip CRC32

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
  sprint("Initial D VFS tools         [files]");
  sprint("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  sprint("file count: "+std::to_string(fileCount));
  for (int i= 0; i < filenames.size(); i++)
  {
    sprint(filenames[i]);
  }
  
}
