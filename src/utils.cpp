#ifndef __utils__
#define __utils__

#include <cstddef>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <iomanip>

class byteManip
{
  private:
    char* file_name;

  public:
    byteManip(char* fname)
    {
      file_name= fname;
    }

    using byte = std::uint8_t;

    void bin(){
      if (std::ifstream file{ file_name, std::ios::binary } )
      {
          const std::size_t nbytes = 1 ;
          std::vector<char> buff(nbytes) ; 
          if( file.read( buff.data(), buff.size() ) ) 
          {
              size_t nread = file.gcount() ; 
              std::vector<byte> bytes( buff.begin(), buff.begin() + nread ) ;
              for( byte b : bytes ) std::cout << std::hex << std::setw(2) << int(b) << ' ' ;
          }
      }
    }
};

#endif // !__utils__
