#ifndef __HEADER_CLI
#define __HEADER_CLI


#include <string>
void mainCLI(int argc, char* argv[]);

namespace CLI
{
  std::string VFSfile;

  void help();
  void files();
}

#endif // !__HEADER_CLI
