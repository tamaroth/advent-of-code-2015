/************************************************************************/
/* Advent of Code:
/* Day 12: JSAbacusFramework.io
/************************************************************************/

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <fstream>
#include <string>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::lexical_cast;
using boost::bad_lexical_cast;

int countElements(const ptree& pt, const bool& filterRed = false)
{
	int local = 0;
	for (const auto& v : pt)
	{
		local += countElements(v.second, filterRed);
		try
		{
			local += lexical_cast<int>(v.second.get_value<std::string>(""));
		}
		catch (const bad_lexical_cast&)
		{
			if (filterRed)
			{
				if ((v.first != "") && (v.second.get_value<std::string>("") == "red"))
					return 0;
			}
		}
	}
	return local;
}

size_t partOne()
{
	std::ifstream infile("data_d12.txt");
	std::string input;
	ptree pt;
	read_json(infile, pt);
	return countElements(pt);
}

size_t partTwo()
{
	std::ifstream infile("data_d12.txt");
	std::string input;
	ptree pt;
	read_json(infile, pt);
	return countElements(pt, true);
}

int main()
{
	std::cout << "Part One: " << partOne() << std::endl;
	std::cout << "Part Two: " << partTwo() << std::endl;
}
