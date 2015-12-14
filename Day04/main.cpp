#include <iostream>
#include <string>

extern "C" {
	#include "md5.h"
}

std::string input = "bgvyzdsv";

uint64_t partOne()
{
	MD5_CTX ctx;
	uint64_t salt = 0;
	unsigned char md5[16];

	do
	{
		unsigned int x1 = 0;
		std::string src = input + std::to_string(salt);
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

	return salt;
}

uint64_t partTwo()
{
	MD5_CTX ctx;
	uint64_t salt = 0;
	unsigned char md5[16];

	do
	{
		unsigned int x1 = 0;
		std::string src = input + std::to_string(salt);
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

	return salt;
}

int main()
{
	std::cout << partOne() << std::endl << partTwo();
}
