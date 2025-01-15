#include "binaryReader.hpp"
#include "utils.cpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <utility>
#include <vector>

binReader::binReader(std::vector<uint8_t> vec) : data{std::move(vec)}
{
  size= data.size();
  pointer= 0;
}

bool binReader::i(size_t x)
{
  bool returnVal= false;
  for (size_t i= 0; i < x; i++)
  {
    debug("[binReader::i] incrementing pointer to: ["+std::to_string(pointer+1)+"/"+std::to_string(size)+"] => "+l2h(pointer+1));
    if (pointer+1 >= size){returnVal= false; debug("[binReader::i] increment failed, out of bounds"); break;}
    else{pointer++; returnVal= true;}
  }
  return returnVal;
}


bool binReader::s(size_t pos)
{
  debug("[binReader::s] setting pointer to: ["+std::to_string(pos)+"/"+std::to_string(size)+"]");
  if (pos > size || pos < 0) {debug("[binReader::s] set failed, out of bounds"); return false;}
  pointer= pos; return true;
}

uint8_t binReader::read()
{
  if (pointer == size)
  {
    sprint("can not read binary file, size exceeded");
    debug("[binReader::read] pointer has exceeded vector size");
    exit(1);
  }
  uint8_t read= data[pointer];
  i(1);
  return read;
}

uint8_t* binReader::read(size_t count)
{
  uint8_t* buff= new uint8_t[count];
  for (size_t i= 0; i < count; i++)
  {
    buff[i]= read();
  }
  return buff;
}
