#include "cli.hpp"
#include "utils.cpp"
#include "vfs.hpp"
#include <cstdlib>
#include <string>

void mainCLI(int argc, char* argv[])
{
  if (argc < 1)
  {
    sprint("No args provided, run --help for more info.");
    exit(0);
  }

  for (int i= 1; i <= argc; i++)
  {
    std::string carg= argv[i];
    debug("[mainCLI] argument: "+ carg+" ["+std::to_string(i)+"/"+std::to_string(argc)+"]");

    if (carg == "--help")
    {CLI::help();}

    if (carg == "--files")
    {CLI::files();}

    if (carg == "--vfs")
    {
      if (i+1 > argc)
      {
        sprint("No arguments after --vfs, expected filename");
        exit(1);
      }
      std::string nextARG(argv[i+1]);
      if (nextARG.rfind("--", 0) == 0)
      {
        sprint("Expected filename after --vfs");
        exit(1);
      }
      CLI::VFSfile= nextARG;
      i++;
      continue;
    }
  }
}

void CLI::files()
{
  debug("[CLI::files] extracting filenames from: "+CLI::VFSfile);
  FileBuffer buff(CLI::VFSfile);
  short type= VFSreunpack::methodType(buff);
  if (type == 0) {sprint("Unsupported file"); exit(1);}
  if (type == 1) // XBB
  {
    VFSreunpack::filesXBB(buff);
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
