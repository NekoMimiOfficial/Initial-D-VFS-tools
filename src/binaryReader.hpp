#ifndef __HEADER_BINARYREADER
#define __HEADER_BINARYREADER

#include <cstddef>
#include <cstdint>
#include <vector>

class binReader
{
  private:
    size_t size;
    size_t pointer;
    std::vector<uint8_t> data;

  public:
    binReader(std::vector<uint8_t> vec);

    // increment counter
    bool i(size_t x);
    // set custom counter position
    bool s(size_t pos);
    // return data and increment once
    uint8_t read();
    //return array of data and increment as each byte returns
    uint8_t* read(size_t count);
};

#endif // !__HEADER_BINARYREADER
