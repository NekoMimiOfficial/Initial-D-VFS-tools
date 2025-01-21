#ifndef __SO_CRC
#define __SO_CRC

#include "utils.cpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

/*CRC32::CRC32(std::vector<uint8_t> i) : data{std::move(i)} {}*/
/**/
/*std::vector<uint8_t> CRC32::hash()*/
/*{*/
/*  std::vector<uint32_t> tableList;*/
/*  tableList.insert(tableList.end(), CRChashMap::tableOffset32.begin(), CRChashMap::tableOffset32.end());*/
/*  tableList.insert(tableList.end(), CRChashMap::tableOffset40.begin(), CRChashMap::tableOffset40.end());*/
/*  tableList.insert(tableList.end(), CRChashMap::tableOffset48.begin(), CRChashMap::tableOffset48.end());*/
/*  tableList.insert(tableList.end(), CRChashMap::tableOffset56.begin(), CRChashMap::tableOffset56.end());*/
/**/
/*  tableList.insert(tableList.end(), CRChashMap::tableLZMA0.begin(), CRChashMap::tableLZMA0.end());*/
/*  tableList.insert(tableList.end(), CRChashMap::tableLZMA1.begin(), CRChashMap::tableLZMA1.end());*/
/*  tableList.insert(tableList.end(), CRChashMap::tableLZMA2.begin(), CRChashMap::tableLZMA2.end());*/
/*  tableList.insert(tableList.end(), CRChashMap::tableLZMA3.begin(), CRChashMap::tableLZMA3.end());*/
/**/
/*  uint32_t crc= 0xffffffff;*/
/*  for (size_t i= 0; i < data.size(); i++)*/
/*  {*/
/*    uint32_t key= (crc ^ data[i]) & 0xFF;*/
/*    crc= tableList[key] ^ (crc >> 8);*/
/*  }*/
/*  debug("[CRC32::hash] hash signature returned: "+l2h(crc));*/
/*  std::vector<uint8_t> res;*/
/*  uint8_t* constr= new uint8_t[4];*/
/*  *(uint32_t*)&constr= crc;*/
/*  res.push_back(constr[0]);*/
/*  res.push_back(constr[1]);*/
/*  res.push_back(constr[2]);*/
/*  res.push_back(constr[3]);*/
/**/
/*  return res;*/
/*}*/
unsigned int crc32(std::vector<uint8_t> data, uint32_t poly)
{
  unsigned int crc = 0xFFFFFFFF;
  size_t size= data.size();

  for (size_t i = 0; i < size; i++)
  {
    uint8_t byte = data[i];
    crc ^= byte;
    for (int j = 0; j < 8; j++) {crc = (crc >> 1) ^ ((crc & 1) ? 0x82F63B78 : 0);}
  }
  crc ^= 0xFFFFFFFF;
  return crc;
} 
#endif
