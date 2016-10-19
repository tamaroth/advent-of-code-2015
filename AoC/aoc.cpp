#include "aoc.hpp"

#include "../Dav01/day01.hpp"
#include "../Day02/Day02.hpp"

int main()
{
	std::map<IDENT, CAoC*> days{
		{IDENT::DAY01, new(std::nothrow) CDay01},
		{IDENT::DAY02, new(std::nothrow) CDay02}
	};

	IDENT id{ IDENT::ALLDAYS };

	if (id == IDENT::ALLDAYS)
	{
		for (const auto& day : days)
		{
			day.second->init();
			std::cout << day.second->part_one() << std::endl;
			std::cout << day.second->part_two() << std::endl;
		}
	}
	else
	{
		days[id]->init();
		std::cout << days[id]->part_one() << std::endl;
		std::cout << days[id]->part_two() << std::endl;
	}

	for (const auto& day : days)
	{
		delete day.second;
	}
}
