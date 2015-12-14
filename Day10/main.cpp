/************************************************************************/
/* Advent of Code:
/* Day 10: Elves Look, Elves Say
/************************************************************************/

#include <iostream>
#include <string>

std::string input = "3113322113";

size_t lookAndSay(int times)
{
	std::string line;;
	std::string newStr = input;
	char lastCh;
	char countChars;

	for (int i = 0; i < times; i++)
	{
		line = newStr;
		newStr = "";
		lastCh = '\0';
		countChars = '\0';
		for (auto ch : line)
		{
			if (ch != lastCh && lastCh != '\0')
			{
				newStr += countChars + 0x30;
				newStr += lastCh;
				countChars = '\0';
			}
			countChars++;
			lastCh = ch;
		}
		newStr += countChars + 0x30;
		newStr += lastCh;
	}

	return newStr.size();
}

size_t partOne()
{
	return lookAndSay(40);
}

size_t partTwo()
{
	return lookAndSay(50);
}

int main()
{
	std::cout << partOne() << std::endl << partTwo();
}
