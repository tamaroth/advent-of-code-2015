/************************************************************************/
/* Advent of Code:
/* Day 5: Doesn't He Have Intern-Elves For This?
/************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

uint32_t isNice(std::string line)
{
	std::vector<std::string> naughtyList = { "ab", "cd", "pq", "xy" };
	std::string vovels = "aeiou";
	int nVovels = 0;
	int nSeries = 0;
	int nNaughty = 0;

	for (auto& v : vovels)
	{
		for (size_t i = 0; i < line.size(); i++)
		{
			if (line[i] == v)
				nVovels++;
		}
	}

	for (size_t i = 0; i < line.size() - 1; i++)
	{
		if (line[i] == line[i + 1])
			nSeries++;
	}

	for (auto& n : naughtyList)
	{
		if (line.find(n) != std::string::npos)
			nNaughty++;
	}

	if (nNaughty)
		return false;

	return static_cast<uint32_t>((nVovels >= 3) && nSeries);
}

uint32_t isNicer(std::string line)
{
	bool foundPair = false;
	bool foundSpace = false;

	for (size_t i = 0; i < line.size() - 2; i++)
	{
		std::string toFind = line.substr(i, 2);
		std::string toCheck = line.substr(i + 2, line.size() - 2 - i);
		if (toCheck.find(toFind) != std::string::npos)
		{
			foundPair = true;
			break;
		}
	}

	for (size_t i = 0; i < line.size() - 2; i++)
	{
		if (line[i] == line[i + 2])
		{
			foundSpace = true;
			break;
		}
	}

	return static_cast<uint32_t>(foundPair && foundSpace);
}

uint32_t partOne()
{
	std::ifstream infile("data_d05.txt");
	std::string input;
	uint32_t nice = 0;

	while (infile >> input)
	{
		nice += isNice(input);
	}
	return nice;
}

uint32_t partTwo()
{
	std::ifstream infile("data_d05.txt");
	std::string input;
	uint32_t nice = 0;

	while (infile >> input)
	{
		nice += isNicer(input);
	}
	return nice;
}

int main()
{
	std::cout << partOne() << std::endl << partTwo();
}
