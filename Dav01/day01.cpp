#include "day01.hpp"

CDay01::CDay01()
{

}

CDay01::~CDay01()
{

}

void CDay01::init()
{
	std::cout << "Day 01!" << std::endl;
	std::ifstream infile("data_d01.txt");

	if (infile.is_open())
	{
		std::getline(infile, m_line);
	}
}

std::string CDay01::part_one() const
{
	high_resolution_clock::time_point t1{ high_resolution_clock::now() };
	std::string res{ "part one: " };

	int floor = 0;
	for (auto& ch : m_line)
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
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	res += std::to_string(floor) + " in " + std::to_string(time_span.count());
	return res;
}

std::string CDay01::part_two() const
{
	high_resolution_clock::time_point t1{ high_resolution_clock::now() };
	std::string res{ "part two: " };

	int floor = 0;
	int position = 0;
	for (auto& ch : m_line)
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
			break;
	}
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	res += std::to_string(position) + " in " + std::to_string(time_span.count());
	return res;
}
