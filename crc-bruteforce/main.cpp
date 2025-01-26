#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <ios>
#include <fstream>
#include <iomanip>
#include <iterator>

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
  std::ostream_iterator<uint8_t> outitr(outfile);
  std::copy(v.begin(), v.end(), outitr);
}

class BoxRender
{
  private:
    int lenght= 14;
    str title;
    int width;
    str info;
    str foot;
    vec body;

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

    void setf(str f) {foot= f;}

    void seti(str i) {info= i;}

    void setb(vec b) {body= b;}

    void render()
    {
      sprint(cornerTL + (horizontal * (width-2-1-info.length())) + Tup + (horizontal * info.length()) + cornerTR);
      sprint(vertical + title + (str(" ") * (width-2-title.length()-1-info.length())) + vertical + info + vertical);
      sprint(Tleft + (horizontal * 5) + Tup + (horizontal * 23) + Tdown + (horizontal * info.length()) + Tright);
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

int main(int ac, char** av)
{
  BoxRender renderer("IDSS CRC Comunist Edition", 43);
  renderer.seti("starting...");
  renderer.render();
}
