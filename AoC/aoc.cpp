#include "aoc.hpp"

#include "../Dav01/day01.hpp"
#include "../Day02/Day02.hpp"
#include "../Day03/day03.hpp"

int main()
{
	std::map<IDENT, std::shared_ptr<CAoC>> days{
		{IDENT::DAY01, std::make_shared<CDay01>()},
		{IDENT::DAY02, std::make_shared<CDay02>()},
		{IDENT::DAY03, std::make_shared<CDay03>()},
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
}
