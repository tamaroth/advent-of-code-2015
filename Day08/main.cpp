/************************************************************************/
/* Advent of Code:
/* Day 8: Matchsticks 
/************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

int countChars(std::string line)
{
	int count = 0;
	for (std::string::iterator it = line.begin(); it != line.end(); it++)
	{
		switch (*it)
		{
		case '"':
			break;
		case '\\':
		{
			if (++it != line.end())
			{
				if (*it == 'x')
					it += 2;
				count++;
			}
			break;
		}
		default:
			count++;
			break;
		}
	}
	return count;
}
std::string escapeLine(std::string line)
{
	std::string res = "\"";

	for (auto x : line)
	{
		switch (x)
		{
		case '"':
			res += "\\\"";
			break;
		case '\\':
			res += "\\\\";
			break;
		default:
			res += x;
			break;
		}
	}
	return res + '"';
}

size_t partOne()
{
	std::ifstream infile("data_d08.txt");
	std::string input;
	size_t codeLen = 0;
	size_t memLen = 0;

	while (std::getline(infile, input))
	{
		codeLen += input.length();
		memLen += countChars(input);
	}

	return codeLen - memLen;
}

size_t partTwo()
{
	std::ifstream infile("data_d08.txt");
	std::string input;
	size_t codeLen = 0;
	size_t memLen = 0;

	while (std::getline(infile, input))
	{
		std::string newLine = escapeLine(input);
		codeLen += newLine.length();
		memLen += countChars(newLine);
	}

	return codeLen - memLen;
}

int main()
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::cout << partOne() << std::endl;
	std::cout << partTwo() << std::endl;
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";
}
