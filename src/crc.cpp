#ifndef __SO_CRC
#define __SO_CRC

#include <cstddef>
#include <cstdint>

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

struct CRC32_s
{
	void generate_table(uint32_t(&table)[256])
	{
		uint32_t polynomial = 0xEDB88320;
		for (uint32_t i = 0; i < 256; i++)
		{
			uint32_t c = i;
			for (size_t j = 0; j < 8; j++)
			{
				if (c & 1) {
					c = polynomial ^ (c >> 1);
				}
				else {
					c >>= 1;
				}
			}
			table[i] = c;
		}
	}

	uint32_t update(uint32_t(&table)[256], uint32_t initial, const void* buf, size_t len)
	{
		uint32_t c = initial ^ 0xFFFFFFFF;
		const uint8_t* u = static_cast<const uint8_t*>(buf);
		for (size_t i = 0; i < len; ++i)
		{
			c = table[(c ^ u[i]) & 0xFF] ^ (c >> 8);
		}
		return c ^ 0xFFFFFFFF;
	}
};

class CRC32
{
private:
	uint32_t table[256];
	CRC32_s crc32_s;
	uint32_t initial;
public:
	CRC32()
		: initial(0xFFFFFFFF)
	{
		crc32_s.generate_table(table);
	}

	void Update(const uint8_t *buf, size_t len)
	{
		initial = crc32_s.update(table, initial, (const void *)buf, len);
	}

	uint32_t GetValue() const
	{
		return initial;
	}
};

#endif
