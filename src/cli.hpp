#ifndef __HEADER_CLI
#define __HEADER_CLI


#include <string>
void mainCLI(int argc, char* argv[]);

class runARGs
{
  public:
    bool arg;
    std::string VFSfile;
};

namespace CLI
{
  void help();
  void files();
  void info();
  void extract();
}

#endif // !__HEADER_CLI
