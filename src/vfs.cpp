#include "vfs.hpp"
#include "counter.cpp"
#include "utils.cpp"
#include <cstdint>
#include <string>

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
  //reset file pointer to 0
  file.set(0);

  //create a counter object for easier data seeking
  Counter c(file.gets());

  //bypass header and magic flag 4
  c.increment(4);
  file.set(c.get());

  int fileCount= file.getb();
  debug("[VFSreunpack::filesXBB] file count: "+std::to_string(fileCount));

  //set pointer back to 0 to loop through each file to get its name
  //but then set it to 32 to bypass the header and get right into the data
  c.custom(31); //index starts at 0
  file.set(c.get());

  for (int i= 1; i <= fileCount; i++)
  {
    uint8_t begptr= file.getb();
  }
}
