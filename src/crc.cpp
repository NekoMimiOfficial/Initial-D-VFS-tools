#ifndef __SO_CRC
#define __SO_CRC

#include "crc.hpp"
/*#include "crcHashmap.cpp"*/
/*#include "utils.cpp"*/
#include <cstddef>
#include <cstdint>
#include <vector>

/*CRCtable32::CRCtable32(std::vector<uint8_t> i) : data{std::move(i)} {}*/

/*void CRCtable32::hash()*/
/*{*/
/*  std::vector<std::vector<uint32_t>> tableList;*/
/*  tableList.push_back(CRChashMap::tableOffset32);*/
/*  tableList.push_back(CRChashMap::tableOffset40);*/
/*  tableList.push_back(CRChashMap::tableOffset48);*/
/*  tableList.push_back(CRChashMap::tableOffset56);*/
/**/
/*  tableList.push_back(CRChashMap::tableLZMA0);*/
/*  tableList.push_back(CRChashMap::tableLZMA1);*/
/*  tableList.push_back(CRChashMap::tableLZMA2);*/
/*  tableList.push_back(CRChashMap::tableLZMA3);*/
/**/
/*  for (std::vector<uint32_t> table : tableList)*/
/*  {*/
/*    uint32_t crc= 0xffffffff;*/
/*    for (size_t i= 0; i < data.size(); i++)*/
/*    {*/
/*      crc = (crc >> 8) ^ table[(crc & 0xff) ^ data[i]];*/
/*    }*/
/*    crc ^= 0xffffffff;*/
/*    debug("[CRCtable32::hash] hash signature returned: "+l2h(crc));*/
/*    uint8_t* output= new uint8_t[4];*/
/**/
/*    output[0]= (uint8_t) (crc >> 24);*/
/*    output[1]= (uint8_t) (crc >> 16);*/
/*    output[2]= (uint8_t) (crc >> 8);*/
/*    output[3]= (uint8_t) (crc);*/
/**/
/*    crc_collection.push_back(output);*/
/*  }*/
/*}*/

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
#endif
