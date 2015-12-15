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
int sum = 0;

void countElements(ptree pt)
{
	for (const auto& v : pt)
	{
		countElements(v.second);
		try
		{
			sum += lexical_cast<int>(v.second.get_value<std::string>(""));
		}
		catch (const bad_lexical_cast&)
		{
		}
	}
}

size_t partOne()
{
	std::ifstream infile("data_d12.txt");
	std::string input;
	ptree pt;

	read_json(infile, pt);
	countElements(pt);
	return sum;
}

int main()
{
	std::cout << partOne();
}
