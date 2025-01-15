#include <fstream>
#include <iostream>
void test()
{
  std::cout << "commencing test... \n";
  std::ifstream buffer;
  char* x= new char [8];
  buffer.open("./test.bin", std::ios::in | std::ios::binary);
  buffer.seekg(0, buffer.end);
  size_t s= buffer.tellg();
  buffer.seekg(0, buffer.beg);
  std::cout << "file size: " << s << "\n";
  std::cout << "File is open: " << buffer.is_open() << "\n";
  buffer.read(x, 8);
  buffer.close();
  std::cout << x << "\n";
}
