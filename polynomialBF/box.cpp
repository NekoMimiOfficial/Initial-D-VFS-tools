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


CLIcontainer::CLIcontainer(str t, int w)
{
  title= t;
  width= w;
}

void CLIcontainer::seto(str o)
{operation= o;}

void CLIcontainer::setb(vec b)
{
  for (int i= 0; i < b.size(); i++)
  {body.push_back(b[i]);}
}

void CLIcontainer::setb(str b)
{
  if (b.length() > (width - 2))
  {
    for (int i = 0; i < b.length(); i += (width - 2)){
        body.push_back(b.substr(i, (width - 2)));
    }
  }else{body.push_back(b);}
}

void CLIcontainer::setf(str f)
{footer= f;}

void CLIcontainer::setw(int w)
{width= w;}

void CLIcontainer::clearb()
{body.clear();}

void CLIcontainer::render()
{
  int title_len= title.length();
  int usable= width - 2 - title_len;

  //width checks
  bool fuse= false;
  if (operation.length() > usable) {fuse= true;}if (title_len > (width - 2))
  {debug("[CLIcontainer::render] title clipped, this is embarassing >///<");
  debug("[CLIcontainer::render] attempting to set reasonable values");
  width= title_len + operation.length() + 8; usable= width - 2 - title_len;}
  if (footer.length() > (width - 2)) {footer.erase((width-5), str::npos); footer += "...";
  debug("[CLIcontainer::render] footer clipped, truncating end chars");}
  debug("[CLIcontainer::render] op clipping status: "+std::to_string(fuse));
  if (fuse)
  {
    sprint("fallback to text rendering, box sizing has clipped");
    sprint(" ");
    sprint(title+"    ["+operation+"]");
    sprint((title_len * str("~"))+(5 * str("~"))+((operation.length()+1) * str("~")));
    for (int i= 0; i < body.size(); i++)
    {
      sprint(body[i]);
    }
    sprint((title_len + 6 + operation.length())*str("~"));
    sprint(footer);
    return;
  }

  for (int i= 0; i < body.size(); i++)
  {
    if (body[i].length() > (width - 2)) {body[i].erase((width - 5), str::npos); body[i]= body[i]+"..."; 
      debug("[CLIcontainer::render] body clipping tripped");}
  }

  str tspacer= (usable - operation.length())*str(" ");
  str spacer= (usable - operation.length()-1)*str(" ");

  sprint(cornerTL+(horizontal * title_len)+(horizontal * ((width - 2)-(title_len + 1)-(operation.length())))+Tup+(horizontal * operation.length())+cornerTR);
  sprint(vertical+title+spacer+vertical+operation+vertical);
  sprint(Tleft+(horizontal * title_len)+(horizontal * ((width - 2)-(title_len + 1)-(operation.length())))+Tdown+(horizontal * operation.length())+Tright);

  for (int i= 0; i < body.size(); i++)
  {
    if (body[i] == "<BOX::SEP>"){
    sprint(Tleft+ ((width - 2)*horizontal) +Tright);}else{
    sprint(vertical+ body[i]+ (((width - 2)-body[i].length())*str(" ")) +vertical);}
  }

  sprint(Tleft+(horizontal*(width - 2))+Tright);
  sprint(vertical+footer+(((width - 2)-footer.length())*str(" "))+vertical);
  sprint(cornerBL+(horizontal* (width - 2))+cornerBR);
}
