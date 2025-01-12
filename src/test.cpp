#include <fstream>
#include <iostream>
void test()
{
  std::cout << "commencing test... \n";
  std::ifstream buffer;
  buffer.open("./test.bin", std::ios::in | std::ios::binary);
  size_t s= buffer.gcount();
  std::cout << "file size: " << s << "\n";
  char* x;
  buffer.seekg(2);
  buffer.read(x, 1);
  std::cout << x << "\n";
}
