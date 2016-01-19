/************************************************************************/
/* Advent of Code:
/* Day 1: Not Quite Lisp
/************************************************************************/

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

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
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::string input;
	std::ifstream infile("data_d01.txt");
	
	while (std::getline(infile, input))
	{
		std::cout << "Part One: " << partOne(input) << std::endl;
		std::cout << "Part Two: " << partTwo(input) << std::endl;
	}
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";
	return 1;
}
