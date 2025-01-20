#include "vfs.cpp"
#include "cli.cpp"

int main (int argc, char *argv[])
{
  FileBuffer winTest("C:/Windows/System32/cmd.exe");
  if (winTest.gets() > 0) {
    #define __WIN32
  }
  mainCLI(argc-1, argv);
  return 0;
}
