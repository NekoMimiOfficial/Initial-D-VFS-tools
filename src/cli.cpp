#include "cli.hpp"
#include "box.hpp"
#include "utils.cpp"
#include "vfs.hpp"
#include <cstdlib>
#include <filesystem>
#include <string>
#include <vector>

using str= std::string;
using vec= std::vector<str>;

bool passedVFS= false;
bool passedPath= false;
bool filesRun= false;
bool infoRun= false;
bool extractRun= false;
bool packRun= false;
std::string VFSfile;
short packType= 0;

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

  
  for (int i= 1; i <= argc; i++)
  {
    std::string carg= argv[i];
    debug("[mainCLI] argument: "+ carg+" ["+std::to_string(i)+"/"+std::to_string(argc)+"]");

    if (carg == "--help")
    {CLI::help(); exit(0);}

    if (carg == "--files")
    {filesRun= true;}

    if (carg == "--info")
    {infoRun= true;}

    if (carg == "--extract")
    {extractRun= true;}

    if (carg.rfind("--vfs=", 0) == 0)
    {
      VFSfile= "";
      for (int i= carg.rfind("=", 0); i <= carg.length(); i++)
      {VFSfile += carg[i+1];}
      if (std::filesystem::exists(VFSfile)) {passedVFS= true;}
    }
  }

  if (filesRun) {CLI::files();}
  if (infoRun) {CLI::info();}
  if (extractRun) {CLI::extract();}

  return;
}

void CLI::files()
{
  if (!(passedVFS)) {bprint("no file specified or it doesn't exist, please use --vfs=path/to/file.bin"); exit(1);}

  debug("[CLI::files] extracting filenames from: "+VFSfile);
  FileBuffer filesBuff(VFSfile);
  short type= VFSreunpack::methodType(filesBuff);
  if (type == 0) {bprint("Unsupported file"); exit(1);}
  if (type == 1) // XBB
  {VFSreunpack::filesXBB(filesBuff);}
  if (type == 2) //ANA
  {VFSreunpack::filesANA(filesBuff);}

  return;
}

void CLI::info()
{
  if (!(passedVFS)) {bprint("no file specified or it doesn't exist, please use --vfs=path/to/file.bin"); exit(1);}

  debug("[CLI::info] showing info for files from: "+VFSfile);
  FileBuffer infoBuff(VFSfile);
  short type= VFSreunpack::methodType(infoBuff);
  if (type == 0) {bprint("Unsupported file"); exit(1);}
  if (type == 1) // XBB
  {VFSreunpack::infoXBB(infoBuff);}
  if (type == 2) // ANA
  {VFSreunpack::infoANA(infoBuff);}
}

void CLI::extract()
{
  if (!(passedVFS)) {bprint("no file specified or doesn't exist, please use --vfs=path/to/file.bin"); exit(1);}

  debug("[CLI::extract] extracting files from: "+VFSfile);
  FileBuffer buff(VFSfile);
  short type= VFSreunpack::methodType(buff);
  if (type == 0) {bprint("Unsupported file"); exit(1);}
  if (type == 1) // XBB
  {VFSreunpack::extractXBB(buff);}
  if (type == 2) //ANA
  {VFSreunpack::extractANA(buff);}
}

void CLI::packXBB()
{
  if (!(passedPath)) {bprint("path not passed or doesn't exist"); exit(1);}
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
  hb.push_back("--info      shows information about a VFS");
  hb.push_back("--extract   extract the files from a VFS");
  hb.push_back("--pack      pack files into (ana/xbb)");
  hb.push_back("    --pack=ANA        packs into ANA");
  hb.push_back("    --pack=XBB        packs into XBB");
  hb.push_back("--vfs       set the VFS file to work on");
  hb.push_back("    --vfs=file.bin    VFS file to extract");
  box.setb(hb);
  box.setf("provided by the catgirrrs :3");
  box.seto("help");
  box.render();
}
