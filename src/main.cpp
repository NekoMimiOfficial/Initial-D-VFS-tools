#include "vfs.cpp"
#include "vfs.hpp"
#include <iostream>

int main (int argc, char *argv[]) {
  std::cout << "Printing second byte for file: " << argv[1] << "\n";
  FileBuffer buff(argv[1]);
  std::cout << checkXBB(buff) << "\n";
  return 0;
}
