#include "box.hpp"
#include "utils.cpp"
#include <string>
#include <vector>

using str= std::string;
using vec= std::vector<str>;

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

int width= 32;

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



void cliBOX::render(str op, vec body, str footer)
{
  str title= "Initial D VFS tools"; int title_len= 19;
  int usable= 8;

  //width checks
  bool fuse= false;
  if (op.length() > usable) {fuse= true;}
  else if (footer.length() > 30) {fuse= true;}
  debug("[cliBOX::render] op, footer clipping status: "+std::to_string(fuse));

  for (int i= 0; i < body.size(); i++)
  {
    if (body[i].length() > 30) {debug("[cliBOX::render] body clipping tripped");}
  }

  str tspacer= (usable - op.length())*str(" ");

  str top= cornerTL+(horizontal * title_len)+(horizontal * (30-20-(op.length())))+Tup+(horizontal * op.length())+cornerTR;
  str rt= vertical+title+tspacer+"  "+vertical+op+vertical;
  str bb= Tleft+(horizontal * title_len)+(horizontal * (30-20-(op.length())))+Tdown+(horizontal * op.length())+Tright;

  sprint(top);
  sprint(rt);
  sprint(bb);

  for (int i= 0; i < body.size(); i++)
  {
    str bodtxt= vertical+ body[i]+((30-body[i].length())*str(" "))+vertical;
    sprint(bodtxt);
  }

  sprint(Tleft+(horizontal*30)+Tright);
  sprint(vertical+footer+((30-footer.length())*str(" "))+vertical);
  sprint(cornerBL+(horizontal*30)+cornerBR);
}
