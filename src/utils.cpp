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

using str= std::string;
using ifIterator= std::istream_iterator<uint8_t>;

std::string __version__= "1.0.0";
bool __APP_DEBUG__= false;

std::string uc2s(uint8_t *str)
//[unsigned char to string] converts a uint8_t array to a string
{
  std::string res= (char*)str;
  return res;
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
  if (__APP_DEBUG__){std::cout << "[DEBUG] " << msg;} //defined from cmake
}

str operator * (str a, unsigned int b) {
    str output = "";
    while (b--) {
        output += a;
    }
    return output;
}

str operator * (unsigned long b, str a) {
    str output = "";
    while (b--) {
        output += a;
    }
    return output;
}

void save2file(std::vector<uint8_t> v, std::string fn)
{
  std::ofstream outfile(fn);
  std::ostream_iterator<uint8_t> outitr(outfile);
  std::copy(v.begin(), v.end(), outitr);
}

class FileBuffer
{
  private:
    //current byte
    uint8_t byte;
    //pointer to current object in vector
    size_t pointer;
    //size of buffer and vector
    size_t dataSize;
    //main data from buffer
    std::vector<uint8_t> data;

  public:
    std::string filename;
    std::string filename_no_ext= "";
    std::string ext= "";
    std::string ext_with_dot;

    FileBuffer(std::string fileName)
    {
      //setting filename and ext
      int dotLoc= fileName.rfind('.', fileName.npos);
      for (int i= 0; i < dotLoc; i++) {filename_no_ext += fileName[i];}
      for (int i= (dotLoc+1); i < fileName.length(); i++) {ext += fileName[i];}
      ext_with_dot= "."+ext; filename= fileName;
      debug("[FileBuffer::FileBuffer] filename: ("+filename_no_ext+") extension: ("+ext+")");

      //initializing and reading size and data from file buffer
      std::ifstream buffer;
      buffer.open(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
      dataSize= buffer.tellg();

      //check if file is empty
      if (dataSize == 0)
      {
        std::cout << "File empty or incorrect filename!" << "\n";
        exit(1);
      }

      data.resize(dataSize);
      buffer.seekg(0, std::ios::beg);
      buffer.read(reinterpret_cast<char *>(data.data()), dataSize);
      
      if (data.size() != dataSize)
      {debug("[FileBuffer::FileBuffer] read size mismatch, corrupt data vector");}
      debug("[FileBuffer::FileBuffer] read data ("+fileName+"): "+std::to_string(dataSize)+" bytes");

      buffer.close();
    }

    ~FileBuffer()
    {
      data.clear();
    }

    void clear()
    {
      data.clear();
    }

    void set(size_t position)
    {
      if ((position < 0) || (position > dataSize)) {return;}

      //sets pointer and saves new data for current byte and blob
      pointer= position;
      byte= data[pointer];
    }

    uint8_t getb()
    {
      //get byte
      return byte;
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
