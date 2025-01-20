#ifndef __HEADER_BOX
#define __HEADER_BOX

#include <cstddef>
#include <string>
#include <vector>

using str= std::string;
using vec= std::vector<str>;

class CLIcontainer
{
  private:
    int width;

    str operation;
    str title;
    
    vec body;
    str footer;

    size_t boxSize;

  public:
    CLIcontainer(str t, int w);

    void seto(str o);
    void setb(vec b);
    void setb(str b);
    void setf(str f);
    void setw(int w);
    void clearb();
    void clearo();

    void render();
};

#endif // !__HEADER_BOX
