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
    uint8_t* blob= new uint8_t[8];
    size_t bufferPosition;
    size_t bufferSize;
    std::basic_ifstream<uint8_t> buffer;

  public:
    FileBuffer(std::string fileName) : buffer(fileName.c_str(), std::ios::in | std::ios::binary)
    {
      buffer.seekg(0, buffer.end);
      bufferSize= buffer.tellg();
      buffer.seekg(0, buffer.beg);
      std::cout << bufferSize << "\n";

      if (bufferSize == 0)
      {
        std::cout << "File empty or incorrect filename!" << "\n";
        exit(1);
      }
    }

    ~FileBuffer()
    {
      buffer.close();
    }

    void seek(size_t position)
    {
      bufferPosition= position;
      buffer.seekg(position, buffer.beg);
      buffer.read(blob, 1);
      currentByte= blob[0];
    }

    uint8_t get()
    {
      return currentByte;
    }

    size_t getPosition()
    {
      return bufferPosition;
    }

    uint8_t* getWord()
    {
      return blob;
    }
};
