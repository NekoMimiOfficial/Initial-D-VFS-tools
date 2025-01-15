#ifndef __SO_UTILS
#define __SO_UTILS

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using ifIterator= std::istream_iterator<uint8_t>;

std::string __version__= "0.0.1";

std::string uc2s(uint8_t *str)
//[unsigned char to string] converts a uint8_t array to a string
{
    return std::string((char *)str);
}

std::string c2s(char* c)
//[char* to string] converts a char array to a string
{
  return std::string(c);
}

template <typename T>
std::string l2h(T i)
{
  std::stringstream stream;
  stream << "0x" 
         << std::setfill('0') << std::setw(sizeof(T)*2) 
         << std::hex << i;
  return stream.str();
}

std::string i2h(uint8_t ui)
{
  char lookup= "0123456789ABCDEF"[ui];
  return "0x"+std::to_string(lookup);
}

void sprint(std::string msg)
{
  std::cout << msg << "\n";
}

void debug(std::string msg)
{
  if (__DEBUG__){sprint("[DEBUG] "+msg);} //defined from cmake
}

class FileBuffer
{
  private:
    //current byte
    uint8_t byte;
    //mainly for making reading the header easier
    uint8_t* blob= new uint8_t[3];
    //pointer to current object in vector
    size_t pointer;
    //size of buffer and vector
    size_t dataSize;
    //main data from buffer
    std::vector<uint8_t> data;

  public:
    FileBuffer(std::string fileName)
    {
      //initializing and reading size and data from file buffer
      std::ifstream buffer;
      buffer.open(fileName.c_str(), std::ios::in | std::ios::binary);
      buffer.seekg(0, buffer.end);
      dataSize= buffer.tellg();
      buffer.seekg(0, buffer.beg);

      //check if file is empty
      if (dataSize == 0)
      {
        std::cout << "File empty or incorrect filename!" << "\n";
        exit(1);
      }

      //iterator to copy data from buffer to vector
      ifIterator iterator(buffer);
      ifIterator endItr;
      //stack overflow
      std::copy(iterator, endItr, std::back_inserter(data));

      buffer.close();
    }

    void set(size_t position)
    {
      //sets pointer and saves new data for current byte and blob
      pointer= position;
      byte= data[pointer];
      blob[0]= data[pointer];
      blob[1]= data[pointer + 1];
      blob[2]= data[pointer + 2];
    }

    uint8_t getb()
    {
      //get byte
      return byte;
    }

    uint8_t* getw()
    {
      //get blob
      return blob;
    }

    size_t getp()
    {
      //get pointer
      return pointer;
    }

    size_t gets()
    {
      //get data size
      return dataSize;
    }

    std::vector<uint8_t> getd()
    {
      //get the entire vector
      return data;
    }
};

#endif // !__SO_UTILS
