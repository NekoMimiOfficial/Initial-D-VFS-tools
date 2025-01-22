#include "utils.cpp"
#include "box.cpp"
#include "binaryReader.cpp"
#include "crc.cpp"
#include <chrono>
#include <csignal>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

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

uint32_t crcKomp= 0x03252feb;
uint32_t currentCRC= 0x00000001;

void savePoly()
{save2file(currentCRC, "save.bin");}

uint32_t loadPoly()
{ if (std::filesystem::exists("./save.bin")){
  FileBuffer fb("save.bin");fb.set(0); uint8_t* buffer= new uint8_t[4]; buffer[0]= fb.getb();fb.set(1);
  buffer[1]= fb.getb(); fb.set(2); buffer[2]= fb.getb(); fb.set(3); buffer[3]= fb.getb();
  uint32_t res= buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24); currentCRC= res; return res;}
  else{savePoly(); return currentCRC;}}

void stop_handler(int s)
{sprint("Closing gracefully..."); savePoly(); exit(0);}

std::string getHashRate(int64_t p1, uint32_t oldCRC)
{
  const int64_t p2= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  int64_t ping= p2 - p1;
  long intDur= ping;
  long seconds= intDur / 1000;
  uint32_t amt= currentCRC - oldCRC;
  int hashed= amt;
  int hash_one_sec= 0;
  if (!(seconds == 0)) {hash_one_sec= hashed / seconds;}

  return std::to_string(hash_one_sec)+"h/s";
}

int main (int argc, char *argv[])
{
  struct sigaction sigINThandler;
  sigINThandler.sa_handler= stop_handler;
  sigemptyset(&sigINThandler.sa_mask);
  sigINThandler.sa_flags= 0;

  sigaction(SIGINT, &sigINThandler, NULL);

  CLIcontainer box("VFS CRC poly brute 9000", 36);
  box.seto("working...");
  box.setb("starting up...");
  box.setf("loading file...");
  box.render();

  if (argc != 2)
  {box.clearb();box.setb("takes only 1 argument: filename");box.seto("Err");box.setf("file loading failed");eraseLines(8);box.render();}
  uint32_t lp= loadPoly();
  FileBuffer fileCrack(argv[1]);
  binReader reader(fileCrack.getd());
  box.setf("hashing...");
  uint32_t epochCRC= lp;
  uint64_t epochTS= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  while (1) {
    box.clearb();
    box.seto(l2h(currentCRC));
    uint32_t komp= crc32(fileCrack.getd(), currentCRC);
    if (komp == crcKomp) {box.setf("found poly: "+l2h(currentCRC)); exit(0);}
    currentCRC++;
    box.setb("Hashing in progress..");
    if ((currentCRC % 0xFF) == 0){box.setf(getHashRate(epochTS, epochCRC));savePoly(); eraseLines(8); box.render();
    epochTS= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); epochCRC= currentCRC;}

  }
  return 0;
}
