#ifndef __HEADER_CLI
#define __HEADER_CLI


#include <string>
void mainCLI(int argc, char* argv[]);

namespace CLI
{
  std::string VFSfile;
  bool arg;

  void help();
  void files();
  void info();
  void extract();
}

#endif // !__HEADER_CLI
