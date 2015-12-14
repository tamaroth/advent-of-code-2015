/************************************************************************/
/* Advent of Code:
/* Day 7: Some Assembly Required
/************************************************************************/

#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <fstream>
#include <tuple>
#include <cctype>
#include <map>

enum class INSTR {
	INSERT,
	AND,
	OR,
	NOT,
	LSHIFT,
	RSHIFT
};

using TOperation = std::tuple<INSTR, std::string, std::string, int>;
std::map<std::string, TOperation> circuit;

template<typename T>
std::vector<T> split(T const& inStr, std::string const& delim)
{
	std::vector<T> retVal;
	boost::split(retVal, inStr, boost::is_any_of(delim));
	return retVal;
}

bool isAlpha(std::string str)
{
	return std::all_of(str.begin(), str.end(), [](char c) { return std::isalpha(c); });
}

bool addToCircuit(std::string line)
{
	std::vector<std::string> tokens = split(line, " ");
	TOperation operation;
	std::string key;

	switch (tokens.size())
	{
	case 3:
	{
		if (!isAlpha(tokens[0]))
		{
			operation = std::make_tuple(INSTR::INSERT, "", "", std::stoi(tokens[0]));
		}
		else {
			operation = std::make_tuple(INSTR::INSERT, tokens[0], "", -1);
		}
		key = tokens[2];
		break;
	}
	case 4:
	{
		operation = std::make_tuple(INSTR::NOT, tokens[1], "", -1);
		key = tokens[3];
		break;
	}
	case 5:
	{
		INSTR instr;
		if (tokens[1] == "AND")
		{
			instr = INSTR::AND;
		}
		else if (tokens[1] == "OR")
		{
			instr = INSTR::OR;
		}
		else if (tokens[1] == "LSHIFT")
		{
			instr = INSTR::LSHIFT;
		}
		else if (tokens[1] == "RSHIFT")
		{
			instr = INSTR::RSHIFT;
		}
		operation = std::make_tuple(instr, tokens[0], tokens[2], -1);
		key = tokens[4];
	}
	default:
		break;
	}
	circuit[key] = operation;
	return true;
}

int computeKey(std::string key)
{
	INSTR instr = std::get<0>(circuit[key]);
	std::string paramA = std::get<1>(circuit[key]);
	std::string paramB = std::get<2>(circuit[key]);
	int retVal = std::get<3>(circuit[key]);

	if (retVal != -1)
		return retVal;

	switch (instr)
	{
	case INSTR::INSERT:
	{
		if (isAlpha(paramA))
		{
			retVal = computeKey(paramA);
		}
		else
		{
			retVal = std::stoi(paramA);
		}
		break;
	}
	case INSTR::NOT:
	{
		uint16_t value = static_cast<uint16_t>(~computeKey(paramA));
		retVal = value;
		break;
	}
	case INSTR::AND:
	{
		if (isAlpha(paramA))
		{
			retVal = computeKey(paramA) & computeKey(paramB);
		}
		else
		{
			retVal = std::stoi(paramA) & computeKey(paramB);
		}
		break;
	}
	case INSTR::OR:
	{
		if (isAlpha(paramA))
		{
			retVal = computeKey(paramA) | computeKey(paramB);
		}
		else
		{
			retVal = std::stoi(paramA) | computeKey(paramB);
		}
		break;
	}
	case INSTR::LSHIFT:
	{
		retVal = computeKey(paramA) << std::stoi(paramB);
		break;
	}
	case INSTR::RSHIFT:
	{
		retVal = computeKey(paramA) >> std::stoi(paramB);
	}
	default:
		break;
	}
	circuit[key] = std::make_tuple(instr, paramA, paramB, retVal);

	return retVal;
}

uint32_t partOne()
{
	std::string input;
	std::ifstream infile("data_d07_1.txt");

	while (std::getline(infile, input))
	{
		addToCircuit(input);
	}
	return computeKey("a");
}

uint32_t partTwo()
{
	std::string input;
	std::ifstream infile("data_d07_2.txt");

	while (std::getline(infile, input))
	{
		addToCircuit(input);
	}
	return computeKey("a");
}

int main()
{
	std::cout << partOne() << std::endl << partTwo();
}
