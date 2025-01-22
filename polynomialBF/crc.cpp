#ifndef __SO_CRC
#define __SO_CRC

#include <cstddef>
#include <cstdint>
#include <vector>

unsigned int crc32(std::vector<uint8_t> data, uint32_t poly)
{
  unsigned int crc = 0xFFFFFFFF;
  size_t size= data.size();

  for (size_t i = 0; i < size; i++)
  {
    uint8_t byte = data[i];
    crc ^= byte;
    for (int j = 0; j < 8; j++) {crc = (crc >> 1) ^ ((crc & 1) ? poly : 0);}
  }
  crc ^= 0xFFFFFFFF;
  return crc;
} 
#endif
