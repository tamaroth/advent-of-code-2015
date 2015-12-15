/************************************************************************/
/* Advent of Code:
/* Day 11: Corporate Policy
/************************************************************************/

#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>
#include <string>

std::string input = "vzbxkghb";

bool isPassOK(std::string passwd)
{
	bool isOK = false;

	if (std::find_if(passwd.begin(), passwd.end(), boost::is_any_of("iol")) != passwd.end())
	{
		return false;
	}

	int times = 0;
	auto it = passwd.begin();
	do
	{
		if ((it = std::adjacent_find(it, passwd.end())) == passwd.end())
		{
			break;
		}
		times++;
		if (it == passwd.end() - 2)
			break;
		it += 2;
	} while (it != passwd.end());
	if (times < 2)
		return false;

	// Any idea how to make this better without all this cluster-fuck?
	for (size_t i = 0; i < passwd.size() - 2; i++)
	{
		if (((passwd[i] + 1) == passwd[i + 1]) && ((passwd[i] + 2) == passwd[i + 2]))
			isOK = true;
	}

	return isOK;
}

std::string generateNew(std::string oldPassword)
{
	std::string newPassword = oldPassword;

	bool found = false;

	while (!found)
	{
		std::reverse(newPassword.begin(), newPassword.end());
		for (auto& ch : newPassword)
		{
			if (ch == 'z')
			{
				ch = 'a';
			}
			else
			{
				ch++;
				break;
			}
		}
		std::reverse(newPassword.begin(), newPassword.end());
		if (isPassOK(newPassword))
			found = true;
	}
	
	return newPassword;
}

std::string partOne(std::string password)
{
	return generateNew(password);
}

std::string partTwo(std::string password)
{
	return generateNew(password);
}

int main()
{
	std::string newPassword = partOne(input);
	std::cout << "Part One: " << newPassword << std::endl;
	std::cout << "Part Two: " << partTwo(newPassword) << std::endl;
}
