#include "counter.hpp"
#include <cstddef>

Counter::Counter(size_t maxSize)
{
  size= maxSize;
}

bool Counter::increment()
{
  if (count+1 >= size){return false;}
  count++; return true;
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
