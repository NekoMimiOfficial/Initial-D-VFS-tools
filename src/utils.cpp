#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

class FileBuffer
{
  private:
    uint8_t currentByte;
    uint8_t* blob;
    size_t bufferPosition;
    size_t bufferSize;
    std::basic_ifstream<uint8_t> buffer;

  public:
    FileBuffer(std::string fileName) : buffer(fileName.c_str(), std::ios::in | std::ios::binary)
    {
      bufferSize= buffer.gcount();
      std::cout << bufferSize << "\n";

      if (bufferSize == 0)
      {
        std::cout << "File empty or incorrect filename!" << "\n";
        exit(1);
      }

      buffer.seekg(0, std::ios::beg);
    }

    ~FileBuffer()
    {
      buffer.close();
    }

    void seek(size_t position)
    {
      buffer.seekg(position);
      buffer.read(blob, 1);
      currentByte= blob[0];
    }

    uint8_t get()
    {
      return currentByte;
    }
};
