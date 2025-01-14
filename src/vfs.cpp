#include "vfs.hpp"
#include "utils.cpp"
#include <cstdint>

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

