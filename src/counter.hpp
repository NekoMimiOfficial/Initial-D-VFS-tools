#ifndef __HEADER_COUNTER
#define __HEADER_COUNTER

#include <cstddef>

class Counter
{
  private:
    size_t count;
    size_t size;

  public:
    Counter(size_t maxSize);

    bool increment();
    bool decrement();
    bool custom (size_t position);
};

#endif // !__HEADER_COUNTER
