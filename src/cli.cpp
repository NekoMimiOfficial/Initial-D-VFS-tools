#include "cli.hpp"
#include "box.hpp"
#include "utils.cpp"
#include "vfs.hpp"
#include <cstdlib>
#include <string>
#include <vector>

using str= std::string;
using vec= std::vector<str>;

void bprint(str txt)
{
  CLIcontainer box("Initial D VFS tools", 35);
  box.seto("Err");
  box.setf("v"+__version__);
  box.setb(txt);
  box.render();
}

void mainCLI(int argc, char* argv[])
{
  if (argc < 1)
  {
    bprint("No args provided, run --help for more info.");
    exit(0);
  }

  CLI::arg= false;
  bool filesRun= false;

  for (int i= 1; i <= argc; i++)
  {
    std::string carg= argv[i];
    debug("[mainCLI] argument: "+ carg+" ["+std::to_string(i)+"/"+std::to_string(argc)+"]");

    if (carg == "--help")
    {CLI::help(); exit(0);}

    if (carg == "--files")
    {filesRun= true;}

    if (carg == "--vfs")
    {
      if (i+1 > argc)
      {
        bprint("No arguments after --vfs, expected filename");
        exit(1);
      }
      std::string nextARG(argv[i+1]);
      if (nextARG.rfind("--", 0) == 0)
      {
        bprint("Expected filename after --vfs");
        exit(1);
      }
      CLI::VFSfile= nextARG;
      CLI::arg= true;
      i++;
      continue;
    }
  }

  if (filesRun) {CLI::files();}
}

void CLI::files()
{
  if (!(CLI::arg)) {bprint("no file specified, please use --vfs path/to/file.bin"); exit(1);}

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
  CLIcontainer box("Neko's VFS tools", 49);
  vec hb;
  hb.push_back(" ^ ^  | Initial D VFS tools              v"+__version__);
  hb.push_back("=UwU= | Apache2 License");
  hb.push_back(" w w  | NekoMimi@NekoLabs LLC 2025+contributors");
  hb.push_back("");
  hb.push_back("--help      shows this help message");
  hb.push_back("--files     shows files inside a VFS");
  hb.push_back("--extract   extract the files from a VFS");
  hb.push_back("--vfs       set the VFS file to work on");
  box.setb(hb);
  box.setf("provided by the catgirrrs :3");
  box.seto("help");
  box.render();
}
