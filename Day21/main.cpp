/************************************************************************/
/* Advent of Code:
/* Day 21: RPG Simulator 20XX
/************************************************************************/

#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <array>

struct Item {
	int		cost;
	int		damage;
	int		armour;
};

struct Player {
	int		hp;
	int		damage;
	int		armour;
};

const std::array<Item, 5> g_weapons = {{{8,4,0},{10,5,0},{25,6,0},{40,7,0},{74,8,0}}};
const std::array<Item, 6> g_armour = {{{0,0,0},{13,0,1},{31,0,2},{53,0,3},{75,0,4},{102,0,5}}};
std::vector<std::vector<Item>> g_rings;
int highPrice = 0;
int lowPrice = 1000;

void generateCombinations(int offset, int k)
{
	const std::array<Item, 7> rings = { { { 0,0,0 },{ 25,1,0 },{ 50,2,0 },{ 100,3,0 },{ 20,0,1 },{ 40,0,2 },{ 80,0,3 } } };
	static std::vector<Item> combination;
	if (k == 0)
	{
		g_rings.push_back(combination);
		return;
	}

	for (int i = offset; i <= rings.size() - k; i++)
	{
		combination.push_back(rings[i]);
		generateCombinations(i + 1, k - 1);
		combination.pop_back();
	}
}

int partOne()
{
	for (const auto weapon : g_weapons)
	{
		for (const auto armour : g_armour)
		{
			for (const auto ring : g_rings)
			{
				Player boss = {100, 8, 2};
				Player player = {100, weapon.damage + ring[0].damage + ring[1].damage, armour.armour + ring[0].armour + ring[1].armour};
				if (boss.hp * std::max(1, boss.damage - player.armour) <= player.hp * std::max(1, player.damage - boss.armour))
				{
					lowPrice = std::min(lowPrice, weapon.cost + armour.cost + ring[0].cost + ring[1].cost);
				}
				else {
					highPrice = std::max(highPrice, weapon.cost + armour.cost + ring[0].cost + ring[1].cost);
				}
			}
		}
	}
	return lowPrice;
}

int partTwo()
{
	return highPrice;
}

int main()
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	generateCombinations(0, 2);
	std::cout << "Part One: " << partOne() << std::endl;
	std::cout << "Part Two: " << partTwo() << std::endl;
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";
	return 0;
}
