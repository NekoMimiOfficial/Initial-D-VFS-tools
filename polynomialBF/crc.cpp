#ifndef __SO_CRC
#define __SO_CRC

#include <cstddef>
#include <cstdint>

struct CRC32_s
{
	void generate_table(uint32_t(&table)[256], uint32_t polynomial)
	{
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
  uint32_t poly;
public:
	CRC32()
		: initial(0xFFFFFFFF)
	{
		crc32_s.generate_table(table, poly);
	}

  void setpoly(uint32_t x)
  {
    poly= x;
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
