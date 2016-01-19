/************************************************************************/
/* Advent of Code:
/* Day 11: Corporate Policy
/************************************************************************/

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <regex>

std::string input = "vzbxkghb";

bool isPassOK(std::string& passwd)
{
	std::regex myreg(R"((.)\1.*(.)\2)");
	bool isOK = false;

	// Password cannot contain letters 'i', 'o' or 'l'.
	if (std::any_of(passwd.begin(), passwd.end(), boost::is_any_of("iol")))
	{
		return false;
	}

	// Password must contain at least two non-overlapping pairs of letters.
	if (!std::regex_search(passwd, myreg))
	{
		return false;
	}

	// Any idea how to make this better without all this cluster-fuck?
	// Password must contain at least one trio consisting of three consecutive letters.
	for (size_t i = 0; i < passwd.size() - 2; i++)
	{
		if (((passwd[i] + 1) == passwd[i + 1]) && ((passwd[i] + 2) == passwd[i + 2]))
			isOK = true;
	}
	return isOK;
}

std::string generateNew(std::string& oldPassword)
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

std::string partOne(std::string& password)
{
	return generateNew(password);
}

std::string partTwo(std::string& password)
{
	return generateNew(password);
}

int main()
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::string newPassword = partOne(input);
	std::cout << "Part One: " << newPassword << std::endl;
	std::cout << "Part Two: " << partTwo(newPassword) << std::endl;
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";

}
