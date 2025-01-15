#include "counter.hpp"
#include "utils.cpp"
#include <cstddef>
#include <string>

Counter::Counter(size_t maxSize)
{
  count= 0;
  size= maxSize;
}

bool Counter::increment()
{
  if ((count+1) >= size){return false;}
  count++; return true;
}

bool Counter::increment(size_t x)
{
  bool returnVal= false;
  for (size_t i= 0; i < x; i++)
  {
    debug("[Counter::increment] incrementing counter to: ["+std::to_string(count+1)+"/"+std::to_string(size)+"]");
    if (count+1 >= size){returnVal= false; debug("[Couter::increment] increment failed, out of bounds"); break;}
    else{count++; returnVal= true;}
  }
  return returnVal;
}

bool Counter::decrement()
{
  if (count-1 <= 0){return false;}
  count--; return true;
}

bool Counter::custom(size_t pos)
{
  if (pos > size || pos < 0){return false;}
  count= pos; return true;
}

size_t Counter::get()
{
  return count;
}

size_t Counter::gets()
{
  return size;
}
