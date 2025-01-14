#include "cli.hpp"
#include "utils.cpp"

void mainCLI(int argc, char* argv[])
{
  if (argc < 2)
  {
    sprint("No args provided, run --help for more info.");
    exit(0);
  }

  for (int i= 0; i < argc; i++)
  {
    if (i == 0 || i == 1){continue;}
    std::string carg= argv[i];

    if (carg == "--help")
    {CLI::help();}
  }
}

void CLI::help()
{
  sprint(" ^ ^  | Initial D VFS tools              v"+__version__);
  sprint("=UwU= | Apache2 License");
  sprint(" w w  | NekoMimi@NekoLabs LLC 2025+contributors");
  sprint("");
  sprint("--help      shows this help message");
  sprint("--files     shows files inside a VFS");
  sprint("--extract   extract the files from a VFS");
  sprint("--vfs       set the VFS file to work on");
}
