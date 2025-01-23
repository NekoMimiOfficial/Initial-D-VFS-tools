#ifndef __HEADER_CRC
#define __HEADER_CRC

#include <cstdint>
#include <vector>

class CRCtable32
{
  private:
    std::vector<uint8_t> data;
    std::vector<uint8_t*> crc_collection;

  public:
    CRCtable32(std::vector<uint8_t> i);
    void hash();
};

#endif // !__HEADER_CRC
