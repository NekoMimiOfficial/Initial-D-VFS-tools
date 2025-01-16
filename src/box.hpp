#ifndef __HEADER_BOX
#define __HEADER_BOX

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

  public:
    CLIcontainer(str t, int w);

    void seto(str o);
    void setb(vec b);
    void setb(str b);
    void setf(str f);
    void setw(int w);

    void render();
};

#endif // !__HEADER_BOX
