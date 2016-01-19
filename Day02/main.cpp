/************************************************************************/
/* Advent of Code:
/* Day 2: I Was Told There Would Be No Math
/************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <regex>

using Size = std::vector<uint32_t>;
using Sizes = std::vector<Size>;

uint32_t getBoxArea(const Size& box)
{
	return 2 * box[0] * box[1] + 2 * box[0] * box[2] + 2 * box[1] * box[2];
}

uint32_t getSmallestSideArea(Size& box)
{
	std::sort(box.begin(), box.end());
	return box[0] * box[1];
}

uint32_t getRibbonLength(Size box)
{
	std::sort(box.begin(), box.end());
	return 2 * box[0] + 2 * box[1] + box[0] * box[1] * box[2];
}

uint64_t partOne(Sizes& sizes)
{
	uint64_t area = 0;

	for (auto& size : sizes)
	{
		area += getBoxArea(size) + getSmallestSideArea(size);
	}
	return area;
}

uint64_t partTwo(Sizes& sizes)
{
	std::ifstream infile("data_d02.txt");
	std::string input;
	uint64_t area = 0;

	for (auto& size : sizes)
	{
		area += getRibbonLength(size);
	}
	return area;
}

void getSizes(Sizes& sizes)
{
	std::ifstream infile("data_d02.txt");
	std::string input;
	std::regex reg(R"((\d+)x(\d+)x(\d+))");
	std::smatch match;

	while (std::getline(infile, input))
	{
		if (std::regex_match(input, match, reg))
		{
			Size size;
			size.push_back(std::stoi(match[1]));
			size.push_back(std::stoi(match[2]));
			size.push_back(std::stoi(match[3]));
			sizes.push_back(size);
		}
	}
	return;
}

int main()
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	Sizes sizes;
	getSizes(sizes);
	std::cout << "Part One: " << partOne(sizes) << std::endl;
	std::cout << "Part Two: " << partTwo(sizes) << std::endl;
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";
	return 1;
}
