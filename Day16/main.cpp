/************************************************************************/
/* Advent of Code:
/* Day 16: Aunt Sue
/************************************************************************/

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <regex>
#include <map>

using Aunt = std::map<std::string, int>;
using Aunts = std::map<int, Aunt>;

int partOne(Aunts& aunts)
{
	Aunt auntSue = {
		{ "children",	3 }, { "cats",		7 }, { "samoyeds",	2 }, { "pomeranians",	3 }, { "akitas",		0 },
		{ "vizslas",	0 }, { "goldfish",	5 }, { "trees",		3 }, { "cars",			2 }, { "perfumes",		1 }
	};
	for (const auto& a : aunts)
	{
		Aunt aunt = a.second;
		bool found = true;
		for (const auto& i : aunt)
		{
			if (auntSue[i.first] != i.second)
			{
				found = false;
				break;
			}
		}
		if (found)
			return a.first;
	}
	return 1;
}

int partTwo(Aunts& aunts)
{
	Aunt auntSue = {
		{ "children",	3 },{ "cats",		7 },{ "samoyeds",	2 },{ "pomeranians",	3 },{ "akitas",		0 },
		{ "vizslas",	0 },{ "goldfish",	5 },{ "trees",		3 },{ "cars",			2 },{ "perfumes",		1 }
	};
	for (const auto& a : aunts)
	{
		Aunt aunt = a.second;
		bool found = true;
		for (const auto& i : aunt)
		{
			if (i.first == "cats" || i.first == "trees")
			{
				if (i.second <= auntSue[i.first])
				{
					found = false;
					break;
				}
			}
			else if (i.first == "pomeranians" || i.first == "goldfish")
			{
				if (i.second >= auntSue[i.first])
				{
					found = false;
					break;
				}
			} else if (auntSue[i.first] != i.second)
			{
				found = false;
				break;
			}
		}
		if (found)
			return a.first;
	}

	return 1;
}

std::map<int, Aunt> getData()
{
	std::map<int, Aunt> aunts;
	std::ifstream infile("data_d16.txt");
	std::string input;
	std::regex scan("Sue (\\d+): (\\w+): (\\d+), (\\w+): (\\d+), (\\w+): (\\d+)");
	std::smatch match;

	while (std::getline(infile, input))
	{
		if (std::regex_match(input, match, scan))
		{
			if (match.size() < 8)
				return std::map<int, Aunt>();
			Aunt aunt;
			aunt[match[2]] = std::stoi(match[3]);
			aunt[match[4]] = std::stoi(match[5]);
			aunt[match[6]] = std::stoi(match[7]);
			aunts[std::stoi(match[1].str())] = aunt;
		}
	}
	return aunts;
}

int main()
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	Aunts aunts = getData();
	std::cout << partOne(aunts) << std::endl;
	std::cout << partTwo(aunts) << std::endl;
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";
}
