#ifndef __HEADER_CRC
#define __HEADER_CRC

#include <cstdint>
#include <vector>

class CRC32
{
  private:
    std::vector<uint8_t> data;

  public:
    CRC32(std::vector<uint8_t> i);
    std::vector<uint8_t> hash();
};

#endif // !__HEADER_CRC
