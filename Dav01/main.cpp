/************************************************************************/
/* Advent of Code:
/* Day 1: Not Quite Lisp
/************************************************************************/

#include <iostream>
#include <string>
#include <fstream>

int partOne(std::string input)
{
	int floor = 0;
	for (auto& ch : input)
	{
		switch (ch)
		{
		case '(':
			floor++;
			break;
		case ')':
			floor--;
		default:
			break;
		}
	}
	return floor;
}

int partTwo(std::string input)
{
	int floor = 0;
	int position = 0;
	for (auto& ch : input)
	{
		position++;
		switch (ch)
		{
		case '(':
			floor++;
			break;
		case ')':
			floor--;
		default:
			break;
		}
		if (floor == -1)
			return position;
	}
	return -1;
}

int main()
{
	std::string input;
	std::ifstream infile("data_d01.txt");
	
	while (std::getline(infile, input))
	{
		std::cout << partOne(input) << std::endl << partTwo(input);
	}
	return 1;
}
