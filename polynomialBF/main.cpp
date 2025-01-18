#include "utils.cpp"
#include "box.cpp"
#include "binaryReader.cpp"
#include "crc.cpp"
#include <csignal>
#include <cstdint>
#include <iostream>

void eraseLines(int count) {
    if (count > 0) {
        std::cout << "\x1b[2K"; // Delete current line
        // i=1 because we included the first line
        for (int i = 1; i < count; i++) {
            std::cout
            << "\x1b[1A" // Move cursor up one
            << "\x1b[2K"; // Delete the entire line
        }
        std::cout << "\r"; // Resume the cursor at beginning of line
    }
}

uint32_t loadPoly();
void savePoly(uint32_t p)
{save2file(p, "save.bin");}

void stop_handler(int s)
{sprint("Closing gracefully...");exit(0);}

int main (int argc, char *argv[])
{
  struct sigaction sigINThandler;
  sigINThandler.sa_handler= stop_handler;
  sigemptyset(&sigINThandler.sa_mask);
  sigINThandler.sa_flags= 0;

  sigaction(SIGINT, &sigINThandler, NULL);

  CLIcontainer box("VFS CRC poly brute 9000", 50);
  box.seto("working...");
  box.setb("starting up...");
  box.setf("loading file...");
  box.render();

  if (argc != 2)
  {box.clearb();box.setb("takes only 1 argument: filename");box.seto("Err");box.setf("file loading failed");eraseLines(8);box.render();}
  while (1) {}
  return 0;
}
