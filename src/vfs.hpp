#ifndef __HEADER_VFS
#define __HEADER_VFS

#include "utils.cpp"
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

bool checkXBB(FileBuffer file);

class XBBstruct
{
  public:
    std::string fileName;
    std::vector<uint8_t> data;

    size_t index;

    uint32_t PTRstart;
    uint32_t PTRend;
    uint32_t PTRfname;
    uint32_t size;
    uint32_t crc32;
    uint8_t magicFlag4;
};

namespace VFSreunpack
{
  short methodType(FileBuffer file);
  void unpackXBB(FileBuffer file);
  void filesXBB(FileBuffer file);
  void infoXBB(FileBuffer file);
}

#endif // !__HEADER_VFS
