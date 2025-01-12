#include "utils.cpp"
#include "vfs.cpp"
#include "test.cpp"
#include <cstdint>
#include <iostream>

int main (int argc, char *argv[]) {
  /*test();*/
  std::cout << "Printing second byte for file: " << argv[1] << "\n";
  FileBuffer buff(argv[1]);
  buff.set(0);
  uint8_t* getTestByte= buff.getw();
  std::cout << getTestByte << "\n";
  return 0;
}
