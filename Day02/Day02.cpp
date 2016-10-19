#include "Day02.hpp"



CDay02::CDay02()
{
}


CDay02::~CDay02()
{
}

void CDay02::init() 
{
	std::cout << "Day 02!" << std::endl;
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
			m_sizes.push_back(size);
		}
	}
	return;
}

std::string CDay02::part_one() const
{
	high_resolution_clock::time_point t1{ high_resolution_clock::now() };
	std::string res{ "part one: " };

	uint64_t area = 0;

	for (auto& size : m_sizes)
	{
		area += getBoxArea(size) + getSmallestSideArea(size);
	}
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	res += std::to_string(area) + " in " + std::to_string(time_span.count());
	return res;
}

std::string CDay02::part_two() const
{
	high_resolution_clock::time_point t1{ high_resolution_clock::now() };
	std::string res{ "part one: " };

	uint64_t area = 0;

	for (auto& size : m_sizes)
	{
		area += getRibbonLength(size);
	}
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	res += std::to_string(area) + " in " + std::to_string(time_span.count());
	return res;
}

uint32_t CDay02::getBoxArea(const Size & box) const
{
	return 2 * box[0] * box[1] + 2 * box[0] * box[2] + 2 * box[1] * box[2];
}

uint32_t CDay02::getSmallestSideArea(Size box) const
{
	std::sort(box.begin(), box.end());
	return box[0] * box[1];
}

uint32_t CDay02::getRibbonLength(Size box) const
{
	std::sort(box.begin(), box.end());
	return 2 * box[0] + 2 * box[1] + box[0] * box[1] * box[2];
}
