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
    bool increment(size_t x);
    bool i(size_t x);
    bool decrement();
    bool custom (size_t position);
    bool c (size_t position);

    size_t get();
    size_t gets();
};

#endif // !__HEADER_COUNTER
