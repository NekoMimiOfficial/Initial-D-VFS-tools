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
std::string PACKpath;
short packType= 0;

void bprint(str txt)
{
  CLIcontainer box("Initial D VFS tools", 35);
  box.seto("Err");
  box.setf("v"+__version__);
  box.setb(txt);
  box.render();
}

void mainCLI(int pargc, char* pargv[])
{
  if (pargc < 1)
  {
    bprint("No args provided, run --help for more info.");
    exit(0);
  }

  
  for (int i= 1; i <= pargc; i++)
  {
    std::string carg= pargv[i];
    debug("[mainCLI] argument: "+ carg+" ["+std::to_string(i)+"/"+std::to_string(pargc)+"]");

    if (carg == "--help")
    {CLI::help(); exit(0);}

    if (carg == "--files")
    {filesRun= true;}

    if (carg == "--info")
    {infoRun= true;}

    if (carg == "--extract")
    {extractRun= true;}

    if (starts_with(carg, "--vfs="))
    {
      VFSfile= "";
      for (int i= carg.rfind("=", carg.npos)+1; i < carg.length(); i++)
      {VFSfile += carg[i];}
      debug("[mainCLI] --vfs: "+VFSfile);
      if (std::filesystem::exists(VFSfile)) {passedVFS= true;}
    }

    if (starts_with(carg, "--pack="))
    {
      packType= 0;
      std::string PTS= "";
      for (int i= carg.rfind("=", carg.npos)+1; i < carg.length(); i++)
      {PTS += carg[i];}
      debug("[mainCLI] --pack: "+PTS);
      if (PTS == "XBB") {packType= 1;}
      if (PTS == "ANA") {packType= 2;}
      debug("[mainCLI] pack type: "+std::to_string(packType));
      packRun= true;
    }

    if (starts_with(carg, "--path="))
    {
      PACKpath= "";
      for (int i= carg.rfind("=", carg.npos)+1; i < carg.length(); i++)
      {PACKpath += carg[i];}
      debug("[mainCLI] --path: "+PACKpath);
      if (std::filesystem::exists(PACKpath)) {passedPath= true;}
    }
  }

  if (filesRun) {CLI::files();}
  if (infoRun) {CLI::info();}
  if (extractRun) {CLI::extract();}
  if (packRun) {CLI::packT();}

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
  if (!std::filesystem::is_directory(PACKpath)) {bprint("--path should point to a directory, not a file."); exit(1);}
}

void CLI::packANA()
{
  if (!(passedPath)) {bprint("path not passed or doesn't exist"); exit(1);}
  if (!std::filesystem::is_directory(PACKpath)) {bprint("--path should point to a directory, not a file."); exit(1);}
}

void CLI::packT()
{
  if (packType == 0) {bprint("wrong option, --pack=[XBB/ANA]"); exit(1);}
  else if (packType == 1) {CLI::packXBB();}
  else if (packType == 2) {CLI::packANA();}

  else {bprint("A miracle happened, it's your unlucky day!"); exit(66);}
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
