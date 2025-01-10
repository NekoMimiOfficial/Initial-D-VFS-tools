#include "vfs.hpp"

Data::Data(char* fname)
{
  VFSFile.open(fname);
}
