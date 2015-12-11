/************************************************************************/
/* Advent of Code:
/* Day 2: I Was Told There Would Be No Math
/************************************************************************/

#include <iostream>
#include <algorithm>
#include <array>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

std::vector<uint32_t> split(std::string const& inStr, std::string const& delim)
{
	std::vector<std::string> tmpvals;
	std::vector<uint32_t> retVal;
	boost::split(tmpvals, inStr, boost::is_any_of(delim));
	std::for_each(tmpvals.begin(), tmpvals.end(), [&](std::string x) { retVal.push_back(std::stoi(x)); return; });
	return retVal;
}

template<class T>
uint32_t getBoxArea(T box)
{
	return 2 * box[0] * box[1] + 2 * box[0] * box[2] + 2 * box[1] * box[2];
}

template<class T>
uint32_t getSmallestSideArea(T box)
{
	std::sort(box.begin(), box.end());
	return box[0] * box[1];
}

template<class T>
uint32_t getRibbonLength(T box)
{
	std::sort(box.begin(), box.end());
	return 2 * box[0] + 2 * box[1] + box[0] * box[1] * box[2];
}

uint64_t partOne()
{
	std::ifstream infile("data_d02.txt");
	std::string input;
	uint64_t area = 0;

	while (std::getline(infile, input))
	{
		std::vector<uint32_t> sizes = split(input, "x");
		area += getBoxArea(sizes) + getSmallestSideArea(sizes);
	}
	return area;
}

uint64_t partTwo()
{
	std::ifstream infile("data_d02.txt");
	std::string input;
	uint64_t area = 0;

	while (std::getline(infile, input))
	{
		std::vector<uint32_t> sizes = split(input, "x");
		area += getRibbonLength(sizes);
	}
	return area;
}

int main()
{
	std::cout << partOne() << std::endl << partTwo();
}
