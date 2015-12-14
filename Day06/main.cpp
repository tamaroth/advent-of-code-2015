/************************************************************************/
/* Advent of Code:
/* Day 6: Probably a Fire Hazard
/************************************************************************/

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <tuple>

enum LIGHT
{
	OFF = 0,
	ON = 1
};

enum class KEYWORD
{
	ON,
	OFF,
	TOGGLE
};

static std::array<std::array<int, 1000>, 1000> garden;

template<typename T>
std::vector<T> split(T const& inStr, std::string const& delim)
{
	std::vector<T> retVal;
	boost::split(retVal, inStr, boost::is_any_of(delim));
	return retVal;
}

void clearGarden()
{
	for (auto& row : garden)
	{
		for (auto& element : row)
		{
			element = 0;
		}
	}
}

bool splitLine(std::string src, KEYWORD& action, int& xs, int& ys, int& xe, int& ye)
{
	std::vector<std::string> tokens = split(src, " ");
	if (tokens[0] == "turn")
	{
		if (tokens[1] == "on")
		{
			action = KEYWORD::ON;
		}
		else
		{
			action = KEYWORD::OFF;
		}
		std::vector<std::string> s_coords = split(tokens[2], ",");
		xs = std::stoi(s_coords[0]);
		ys = std::stoi(s_coords[1]);
		std::vector<std::string> l_coords = split(tokens[4], ",");
		xe = std::stoi(l_coords[0]);
		ye = std::stoi(l_coords[1]);
	}
	else if (tokens[0] == "toggle")
	{
		action = KEYWORD::TOGGLE;
		std::vector<std::string> s_coords = split(tokens[1], ",");
		xs = std::stoi(s_coords[0]);
		ys = std::stoi(s_coords[1]);
		std::vector<std::string> l_coords = split(tokens[3], ",");
		xe = std::stoi(l_coords[0]);
		ye = std::stoi(l_coords[1]);
	}
	else
	{
		return false;
	}
	return true;
}

uint32_t partOne()
{
	std::ifstream infile("data_d06.txt");
	std::string input;
	uint32_t lit = 0;
	KEYWORD kw;

	clearGarden();
	while (std::getline(infile, input))
	{
		int xs = 0, ys = 0, xe = 0, ye = 0;
		splitLine(input, kw, xs, ys, xe, ye);
		for (int i = xs; i <= xe; i++)
		{
			for (int j = ys; j <= ye; j++)
			{
				switch (kw)
				{
				case KEYWORD::ON:
					garden[i][j] = LIGHT::ON;
					break;
				case KEYWORD::OFF:
					garden[i][j] = LIGHT::OFF;
					break;
				case KEYWORD::TOGGLE:
					garden[i][j] = static_cast<LIGHT>(!garden[i][j]);
					break;
				default:
					break;
				}
			}
		}
	}

	for (auto& row : garden)
	{
		for (auto& element : row)
		{
			if (element == LIGHT::ON)
				lit++;
		}
	}
	return lit;
}

uint32_t partTwo()
{
	std::ifstream infile("data_d06.txt");
	std::string input;
	uint32_t brightness = 0;
	KEYWORD kw;

	clearGarden();
	while (std::getline(infile, input))
	{
		int xs = 0, ys = 0, xe = 0, ye = 0;
		splitLine(input, kw, xs, ys, xe, ye);
		for (int i = xs; i <= xe; i++)
		{
			for (int j = ys; j <= ye; j++)
			{
				switch (kw)
				{
				case KEYWORD::ON:
					garden[i][j]++;
					break;
				case KEYWORD::OFF:
					if (garden[i][j] >= 1)
						garden[i][j]--;
					break;
				case KEYWORD::TOGGLE:
					garden[i][j] += 2;
					break;
				default:
					break;
				}
			}
		}
	}

	for (auto& row : garden)
	{
		for (auto& element : row)
		{
			brightness += element;
		}
	}
	return brightness;
}

int main()
{
	std::cout << partOne() << std::endl << partTwo();
}
