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
    uint32_t crc32;
};

class ANAstruct
{
  public:
    std::string filename;
    std::vector<uint8_t> data;

    uint32_t PTRstart;
    uint32_t PTRend;
    size_t index;
};

namespace VFSreunpack
{
  short methodType(FileBuffer file);
  
  void filesXBB(FileBuffer file);
  void infoXBB(FileBuffer file);
  void extractXBB(FileBuffer file);

  void filesANA(FileBuffer file);
  void infoANA(FileBuffer file);
  void extractANA(FileBuffer file);
}

#endif // !__HEADER_VFS
