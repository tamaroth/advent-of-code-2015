#include "day04.hpp"



CDay04::CDay04()
{
}


CDay04::~CDay04()
{
}

void CDay04::init()
{

}

std::string CDay04::part_one() const
{
	high_resolution_clock::time_point t1{ high_resolution_clock::now() };
	std::string res{ "part one: " };

	MD5_CTX ctx;
	uint64_t salt = 0;
	unsigned char md5[16];

	do
	{
		unsigned int x1 = 0;
		std::string src = m_input + std::to_string(salt);
		MD5Init(&ctx);
		MD5Update(&ctx, reinterpret_cast<unsigned char *>(const_cast<char*>(src.c_str())), static_cast<uint32_t>(src.length()));
		MD5Final(md5, &ctx);
		x1 = *(unsigned int *)(&md5[0]);

		if ((x1 & 0x00F0FFFF) == 0)
		{
			break;
		}
		salt++;
	} while (salt != -1);

	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	res += std::to_string(salt) + " in " + std::to_string(time_span.count());
	return res;
}

std::string CDay04::part_two() const
{
	high_resolution_clock::time_point t1{ high_resolution_clock::now() };
	std::string res{ "part two: " };

	MD5_CTX ctx;
	uint64_t salt = 0;
	unsigned char md5[16];

	do
	{
		unsigned int x1 = 0;
		std::string src = m_input + std::to_string(salt);
		MD5Init(&ctx);
		MD5Update(&ctx, reinterpret_cast<unsigned char *>(const_cast<char*>(src.c_str())), static_cast<uint32_t>(src.length()));
		MD5Final(md5, &ctx);
		x1 = *(unsigned int *)(&md5[0]);

		if ((x1 & 0x00FFFFFF) == 0)
		{
			break;
		}
		salt++;
	} while (salt != -1);

	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	res += std::to_string(salt) + " in " + std::to_string(time_span.count());
	return res;
}
