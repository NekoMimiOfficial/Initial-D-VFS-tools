#include <IDSSVfs/ANA.hpp>
#include <IDSSVfs/XBB.hpp>
#include <IDSSVfs/typeCheck.hpp>
#include <IDSSVfs/extractXBB.hpp>
#include <IDSSVfs/extractANA.hpp>
#include <NMPP/Converters.hpp>
#include <NMPP/Conditions.hpp>
#include <NMPP/FileIO.hpp>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

struct AppOptions
{
  bool extract= false;
  bool pack= false;
  bool info= false;

  std::string vfs_file;
  std::string out_dir;
};

std::string parseArgs(int argc, char* argv[], AppOptions& options)
{
    std::vector<std::string> positional_args;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-o")
        {
            if (i + 1 < argc)
            {
                options.out_dir = argv[++i];
            }
            else
            {
                return "Error: -o flag requires a directory path.";
            }
        }
        else if (arg[0] == '-')
        {
            for (size_t j = 1; j < arg.length(); ++j)
            {
                char flag = arg[j];
                switch (flag)
                {
                    case 'e':
                        options.extract = true;
                        break;
                    case 'i':
                        options.info = true;
                        break;
                    case 'p':
                        options.pack = true;
                        break;
                    default:
                        std::string error_msg = "Error: Unrecognized flag '";
                        error_msg += flag;
                        error_msg += "'.";
                        return error_msg;
                }
            }
        }
        else if (arg == "--version")
        {
          return "Initial D VFS Tools v2.0.0";
        }
        else if (arg == "--help")
        {
          return "No help message for now";
        }
        else
        {
            positional_args.push_back(arg);
        }
    }

    if (positional_args.size() != 1)
    {
        return "Error: Exactly one input VFS file is required.";
    }
    options.vfs_file = positional_args[0];

    return "";
}

void infoANA(AppOptions options)
{
  ANAExtractor Extractor(options.vfs_file);
  struct ANA ana= Extractor.extract();
  if (ana.valid)
  {
    std::cout << "ANA files: " << ana.file_count << "\n";
    for (ANAitem file : ana.items)
    {
      std::cout << "index: " << file.index << " | " << convert::hex(file.ptr_start) << " | " << convert::hex(file.ptr_size)<< " | " << file.filename << "\n";
    }
  }
  else {std::cout << "The ANA file provided is invalid.\n";}
}

void infoXBB(AppOptions options)
{
  XBBExtractor Extractor(options.vfs_file);
  struct XBB xbb= Extractor.extract();
  if (xbb.valid)
  {
    std::cout << "XBB files: " << xbb.file_count << "\n";
    for (XBBitem file : xbb.items)
    {
      std::cout << "index: " << file.index << " | " << convert::hex(file.ptr_start) << " | " << convert::hex(file.ptr_size)<< " | " << convert::hex(file.crc) << " | " << file.filename << "\n";
    }
  }
  else {std::cout << "The XBB file provided is invalid.\n";}
}

void extANA(AppOptions options)
{
  ANAExtractor Extractor(options.vfs_file);
  struct ANA ana= Extractor.extract();
  if (options.out_dir.empty())
  {
    std::cerr << "You must specify an output directory for the extraction flag.\n";
    exit(22);
  }
  if (ana.valid)
  {
    std::filesystem::create_directory("./"+options.out_dir);
    for (ANAitem file : ana.items)
    {
      save_byte(file.data, "./"+options.out_dir+"/"+file.filename);
    }
    std::cout << "Extracted " << ana.file_count << " files.\n";

  }
  else {std::cout << "The ANA file provided is invalid.\n";}
}

void extXBB(AppOptions options)
{
  XBBExtractor Extractor(options.vfs_file);
  struct XBB xbb= Extractor.extract();
  if (options.out_dir.empty())
  {
    std::cerr << "You must specify an output directory for the extraction flag.\n";
    exit(22);
  }
  if (xbb.valid)
  {
    std::filesystem::create_directory("./"+options.out_dir);
    for (XBBitem file : xbb.items)
    {
      save_byte(file.data, "./"+options.out_dir+"/"+file.filename);
    }
    std::cout << "Extracted " << xbb.file_count << " files.\n";
  }
  else {std::cout << "The XBB file provided is invalid.\n";}
}

int main (int argc, char *argv[])
{
  AppOptions options;
  std::string errorMessage = parseArgs(argc, argv, options);

  if (!errorMessage.empty() && starts_with(errorMessage, "Error"))
  {
    std::cerr << errorMessage << std::endl;
    std::cerr << "Usage: " << argv[0] << " [-eip] FILE -o output_dir" << std::endl;
    return 1;
  }else if (!errorMessage.empty())
  {
    std::cout << errorMessage << std::endl;
    return 0;
  }

  if (options.info)
  {
    VFSType type= checkVFS(options.vfs_file);
    switch (type)
    {
      case VFSType::XBB:
        infoXBB(options);
        break;

      case VFSType::ANA:
        infoANA(options);
        break;

      case VFSType::ERR:
        std::cout << "You seem to have provided a generic file that is not a VFS file.\n";
        break;
    }
  }

  if (options.extract)
  {
    VFSType type= checkVFS(options.vfs_file);
    switch (type)
    {
      case VFSType::XBB:
        extXBB(options);
        break;

      case VFSType::ANA:
        extANA(options);
        break;

      case VFSType::ERR:
        std::cout << "You seem to have provided a generic file that is not a VFS file.\n";
        break;
    }
  }

  return 0;
}
