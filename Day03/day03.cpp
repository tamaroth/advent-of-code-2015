#include "day03.hpp"



CDay03::CDay03()
{
}


CDay03::~CDay03()
{
}

void CDay03::init()
{
	std::cout << "Day 03!" << std::endl;
}

std::string CDay03::part_one() const
{
	high_resolution_clock::time_point t1{ high_resolution_clock::now() };
	std::string res{ "part one: " };
	std::map<std::tuple<int, int>, int> mymap;
	std::tuple<int, int> curr;
	int x = 0, y = 0;

	mymap[std::make_tuple(0, 0)] = 1;

	for (auto& a : m_input)
	{
		switch (a)
		{
		case '<':
			curr = std::make_tuple(--x, y);
			break;
		case '>':
			curr = std::make_tuple(++x, y);
			break;
		case '^':
			curr = std::make_tuple(x, ++y);
			break;
		case 'v':
			curr = std::make_tuple(x, --y);
			break;
		default:
			break;
		}
		mymap[curr] = 1;
	}

	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	res += std::to_string(mymap.size()) + " in " + std::to_string(time_span.count());
	return res;
}

std::string CDay03::part_two() const
{
	high_resolution_clock::time_point t1{ high_resolution_clock::now() };
	std::string res{ "part two: " };
	std::map<std::tuple<int, int>, int> mymap;
	std::tuple<int, int> curr;
	int s_x = 0, s_y = 0;
	int r_x = 0, r_y = 0;
	bool santa_turn = true;

	mymap[std::make_tuple(0, 0)] = 1;

	for (auto& a : m_input)
	{
		switch (a)
		{
		case '<':
			curr = std::make_tuple(santa_turn ? --s_x : --r_x, santa_turn ? s_y : r_y);
			break;
		case '>':
			curr = std::make_tuple(santa_turn ? ++s_x : ++r_x, santa_turn ? s_y : r_y);
			break;
		case '^':
			curr = std::make_tuple(santa_turn ? s_x : r_x, santa_turn ? ++s_y : ++r_y);
			break;
		case 'v':
			curr = std::make_tuple(santa_turn ? s_x : r_x, santa_turn ? --s_y : --r_y);
			break;
		default:
			break;
		}
		mymap[curr] = 1;
		santa_turn = !santa_turn;
	}

	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	res += std::to_string(mymap.size()) + " in " + std::to_string(time_span.count());
	return res;
}
