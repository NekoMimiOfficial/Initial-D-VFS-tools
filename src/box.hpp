#ifndef __HEADER_BOX
#define __HEADER_BOX

#include <string>
#include <vector>

using str= std::string;
using vec= std::vector<str>;

namespace cliBOX
{
  void render(str op, vec body, str footer);
};

#endif // !__HEADER_BOX
