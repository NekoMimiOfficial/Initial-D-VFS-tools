#ifndef __COUNTER__
#define __COUNTER__

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

#endif // !__COUNTER__
