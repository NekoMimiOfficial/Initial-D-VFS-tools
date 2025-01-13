#include "vfs.hpp"
#include <cstdint>

bool checkXBB(FileBuffer file)
{
  file.set(0);
  uint8_t* check= new uint8_t[3];
  return (uc2s(file.getw()) == "XBB");
}

