#ifndef __InitDVFS__
#define __InitDVFS__

#include <cstddef>
#include <fstream>
#include <vector>
using namespace std;

class VFSdataStruct
{
  public:
    size_t index_pos;

    char* file_begin;
    size_t file_size;
    char* file_end;
    char* file_unhash;

    char* file_data;
    char* file_name;
};

class VFSdataCollect
{
  public:
    vector<VFSdataStruct> Files;
    vector<char*> ByteBlob;
};

class Data
{
  private:
    ifstream VFSFile;

  public:
    Data(char* fname);
};

#endif // !__InitDVFS__
