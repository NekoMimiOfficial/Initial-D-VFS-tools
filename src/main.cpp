#include "utils.cpp"
#include "vfs.cpp"
#include <cstdint>
#include <iostream>

int main (int argc, char *argv[]) {
  FileBuffer buff(argv[1]);
  buff.seek(2);
  uint8_t getTestByte= buff.get();
  std::cout << getTestByte << "\n";
  return 0;
}
