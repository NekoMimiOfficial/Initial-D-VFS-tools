#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <ios>
#include <fstream>
#include <iomanip>
#include <thread>
#include <sched.h>

using str= std::string;
using vec= std::vector<str>;
using vec8= std::vector<uint8_t>;
using vec32= std::vector<uint32_t>;

str cornerTR= "┐";
str cornerTL= "┌";
str cornerBR= "┘";
str cornerBL= "└";

str Tup= "┬";
str Tdown= "┴";
str Tleft= "├";
str Tright= "┤";

str cross= "┼";

str horizontal= "─";
str vertical= "│";

str p0= "000";
str p1= "000";
str p2= "000";
str p3= "000";
str p4= "000";
str p5= "000";
str p6= "000";
str p7= "000";
str pt= "000";

uint32_t t0= 0x00000000;
uint32_t t1= 0x02000000;
uint32_t t2= 0x04000000;
uint32_t t3= 0x06000000;
uint32_t t4= 0x08000000;
uint32_t t5= 0x0A000000;
uint32_t t6= 0x0C000000;
uint32_t t7= 0x0E000000;

uint32_t crc_hash= 0x2492c3ca;
vec8 crc_data= 
{
0x4D, 0x49, 0x47, 0x2E, 0x30, 0x30, 0x2E, 0x31, 0x50, 0x53, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x50, 0x02, 0x00, 0x00, 0x50, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x04, 0x00, 0x01, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x10, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x54, 0x24, 0x33, 0x33, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xF5, 0x67, 0xB6, 0x6B, 0x04, 0x44, 0x44, 0x44, 0x44, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0xAA, 0x9E, 0xD9, 0xFD, 0x24, 0xF4, 0xFF, 0xFF, 0xDF, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x6F, 0x6F, 0xD9, 0xFD, 0x26, 0x44, 0x44, 0x44, 0x44, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x93, 0xBF, 0x9F, 0xFA, 0xFF, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA3, 0x9E, 0xD6, 0xD8, 0x9D, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0xBD, 0xDC, 0xD9, 0x9D, 0x23, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x7D, 0x9F, 0xD9, 0x9D, 0x45, 0x66, 0x66, 0x66, 0x66, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x8D, 0xDF, 0x76, 0x46, 0x45, 0xDD, 0xDD, 0xDD, 0xDD, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x9A, 0x57, 0xDA, 0xDD, 0x46, 0x44, 0x44, 0x44, 0x44, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x33, 0x33, 0x44, 0x44, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x10, 0x00, 0x01, 0x00, 0x20, 0x00, 0x10, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x00, 0x00, 0xE1, 0x00, 0x00, 0x00, 0xFF, 0x22, 0x22, 0x22, 0xFE, 0x76, 0x76, 0x76, 0xFF, 0x8E, 0x8E, 0x8E, 0xFF, 0xA3, 0xA3, 0xA3, 0xFF, 0xB6, 0xB6, 0xB6, 0xFF, 0xC7, 0xC7, 0xC7, 0xFF, 0xD6, 0xD6, 0xD6, 0xFF, 0xE3, 0xE3, 0xE3, 0xFF, 0xED, 0xED, 0xED, 0xFF, 0xF5, 0xF5, 0xF5, 0xFF, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
};

template <typename T>
std::string l2h(T i)
{
  std::stringstream stream;
  stream << "0x" 
         << std::setfill('0') << std::setw(sizeof(T)*2) 
         << std::hex << i;
  return stream.str();
}

bool starts_with(std::string str, std::string startValue)
{
  return (str.rfind(startValue, 0) == 0);
}

void sprint(std::string msg)
{
  std::cout << msg << "\n";
}

str operator * (str a, unsigned int b) {
    str output = "";
    while (b--) {
        output += a;
    }
    return output;
}

str operator * (unsigned long b, str a) {
    str output = "";
    while (b--) {
        output += a;
    }
    return output;
}

void save2file(std::vector<uint8_t> v, std::string fn)
{
  std::ofstream outfile(fn);
  outfile.write(reinterpret_cast<const char*>(v.data()), v.size() * sizeof(uint8_t));
  outfile.close();
}

void save_snapshot()
{
  vec32 v;
  v.push_back(t0);
  v.push_back(t1);
  v.push_back(t2);
  v.push_back(t3);
  v.push_back(t4);
  v.push_back(t5);
  v.push_back(t6);
  v.push_back(t7);
  std::ofstream of("save.bin", std::ios::out | std::ios::binary);
  of.write(reinterpret_cast<const char*>(v.data()), v.size() * sizeof(uint32_t));
  of.close();
}

void load_snapshot()
{
  if(!(std::filesystem::exists("save.bin"))) {save_snapshot();}

  std::ifstream buffer;
  buffer.open("save.bin", std::ios::in | std::ios::binary | std::ios::ate);
  size_t bl= buffer.tellg();

  if (bl == 0) {sprint("Fatal error, incorrect save read..."); exit(1);}

  vec32 data; data.resize(bl);
  buffer.seekg(0, std::ios::beg);
  buffer.read(reinterpret_cast<char *>(data.data()), bl);
  t0= data[0];
  t1= data[1];
  t2= data[2];
  t3= data[3];
  t4= data[4];
  t5= data[5];
  t6= data[6];
  t7= data[7];
}

unsigned int crc32(std::vector<uint8_t> data, uint32_t poly)
{
  unsigned int crc = 0xFFFFFFFF;
  size_t size= data.size();
  for (size_t i = 0; i < size; i++)
  {
    uint8_t byte = data[i];
    crc ^= byte;
    for (int j = 0; j < 8; j++) {crc = (crc >> 1) ^ ((crc & 1) ? poly : 0);}
  }
  crc ^= 0xFFFFFFFF;
  return crc;
} 

class BoxRender
{
  private:
    int lenght= 256;
    str title;
    int width;
    str info;

  public:
    BoxRender(str t, int w) {width= w; title= t;}

    void cls() {
      if (lenght > 0) {
        std::cout << "\x1b[2K";
        for (int i = 1; i < lenght; i++)
        {
          std::cout
            << "\x1b[1A"
            << "\x1b[2K";
        }
        std::cout << "\r";
      }
    }

    void seti(str i) {info= i;}

    void render()
    {
      sprint(cornerTL + (horizontal * (width-2-1-info.length())) + Tup + (horizontal * info.length()) + cornerTR);
      sprint(vertical + title + (str(" ") * (width-2-title.length()-1-info.length())) + vertical + info + vertical);
      sprint(Tleft + (horizontal * 5) + Tup + (horizontal * 24) + Tdown + (horizontal * info.length()) + Tright);
      sprint(vertical + p0 + " %" + vertical + l2h(t0) + "  " + l2h(t1) + "  " + l2h(t2) + " " + vertical);
      sprint(vertical + p1 + " %" + vertical + l2h(t3) + "  " + l2h(t4) + "  " + l2h(t5) + " " + vertical);
      sprint(vertical + p2 + " %" + vertical + l2h(t6) + "              " + l2h(t7) + " " + vertical);
      sprint(vertical + p3 + " %" + Tleft + (horizontal * 35) + Tright);
      sprint(vertical + p4 + " %" + vertical + "  ^ ^  | CRC un-sega-fy            " + vertical);
      sprint(vertical + p5 + " %" + vertical + " =UwU= | Tool to find a polynomial " + vertical);
      sprint(vertical + p6 + " %" + vertical + "  w w  | of the IDSS PSP title     " + vertical);
      sprint(vertical + p7 + " %" + vertical + "                                   " + vertical);
      sprint(vertical + pt + " %" + vertical + " Please wait while we do our magic " + vertical);
      sprint(cornerBL + (horizontal * 5) + Tdown + (horizontal * 35) + cornerBR);
    }

};

void set_thread_affinity(std::thread& thread, int cpu_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu_id, &cpuset);
    int rc = pthread_setaffinity_np(thread.native_handle(), sizeof(cpu_set_t), &cpuset);
    if (rc != 0) {
        sprint("Error setting thread affinity for CPU " + std::to_string(cpu_id));
    }
}

void worker(short thread, BoxRender r)
{
  if (thread > 7) {sprint("Fatal error, high thread count..."); exit(1);}

  uint32_t s, e, ps;
  switch (thread)
  {
    case 0:
      s= t0;
      ps= 0x00000000;
      e= 0x02000000;
      break;

    case 1:
      s= t1;
      ps= 0x02000000;
      e= 0x04000000;
      break;

    case 2:
      s= t2;
      ps= 0x04000000;
      e= 0x06000000;
      break;

    case 3:
      s= t3;
      ps= 0x06000000;
      e= 0x08000000;
      break;

    case 4:
      s= t4;
      ps= 0x08000000;
      e= 0x0A000000;
      break;

    case 5:
      s= t5;
      ps= 0x0A000000;
      e= 0x0C000000;
      break;

    case 6:
      s= t6;
      ps= 0x0C000000;
      e= 0x0E000000;
      break;

    case 7:
      s= t7;
      ps= 0x0E000000;
      e= 0xFFFFFFFF;
      break;
  }

  for (uint32_t ind= s; ind <= e; ind++)
  {
    uint32_t t_c_poly= crc32(crc_data, ind);
    if (ind % 0xFFFF == 0)
    {
      int percentage= (ind-ps) * 0x64 / 0x01FFFFFF;
      str spcnt= std::to_string(percentage);
      if (spcnt.length() == 1) {spcnt= "00"+spcnt;}
      else if (spcnt.length() == 2) {spcnt= "0"+spcnt;}
      switch (thread)
      {
        case 0:
          t0= ind; break;

        case 1:
          t1= ind; break;

        case 2:
          t2= ind; break;

        case 3:
          t3= ind; break;

        case 4:
          t4= ind; break;

        case 5:
          t5= ind; break;

        case 6:
          t6= ind; break;

        case 7:
          t7= ind; break;
      }

      switch (thread)
      {
        case 0:
          p0= spcnt; break;

        case 1:
          p1= spcnt; break;

        case 2:
          p2= spcnt; break;

        case 3:
          p3= spcnt; break;

        case 4:
          p4= spcnt; break;

        case 5:
          p5= spcnt; break;

        case 6:
          p6= spcnt; break;

        case 7:
          p7= spcnt; break;
      }

      int ipt= (std::stoi(p0) + std::stoi(p1) + std::stoi(p2) + std::stoi(p3) + std::stoi(p4) + std::stoi(p5) + std::stoi(p6) + std::stoi(p7)) / 8;
      pt= std::to_string(percentage);
      if (pt.length() == 1) {pt= "00"+pt;}
      else if (pt.length() == 2) {pt= "0"+pt;}

      save_snapshot();
      r.cls(); r.render();
    }
    if (t_c_poly == crc_hash)
    {
      sprint("Found Polynomial!!   "+l2h(t_c_poly));
      vec8 sv; sv.push_back(t_c_poly);
      save2file(sv, "poly.bin");
      exit(0);
    }
  }
}

void spawnThreads(int n, BoxRender r)
{
  if (n > 8) {sprint("Error, can't spawn more than 8 threads..."); exit(1);}

  std::vector<std::thread> threads(n);
  for (int i = 0; i < n; i++) {threads[i] = std::thread(worker, i, r); set_thread_affinity(threads[i], i);}
  for (auto& th : threads) {th.join();}
}

int main(int ac, char** av)
{
  load_snapshot();
  BoxRender renderer("IDSS CRC Comunist Edition", 43);
  renderer.seti("hashing...");
  renderer.render();
  spawnThreads(8, renderer);
}
