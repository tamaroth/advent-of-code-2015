/************************************************************************/
/* Advent of Code:
/* Day 15: Science for Hungry People
/************************************************************************/

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include <map>
using Spoons = std::vector<std::vector<int>>;
struct Characteristic {
	int64_t Capacity;
	int64_t Durability;
	int64_t Flavor;
	int64_t Texture;
	int64_t Calories;
};
Characteristic sugar = { 3, 0, 0, -3, 2 };
Characteristic sprinkles = { -3, 3, 0, 0, 9 };
Characteristic candy = { -1, 0, 4, 0, 1 };
Characteristic chocolate = { 0, 0, -2, 2, 8 };
std::array<Characteristic, 4> ingrdedients = {
	sugar,
	sprinkles,
	candy,
	chocolate
};

std::vector<int> generate(int x1, int x2, int x3)
{
	std::vector<int> values{ x1, x2, x3 };
	std::sort(values.begin(), values.end());
	std::vector<int> retVal = {
		values[0] - 1,
		values[1] - values[0] - 1,
		values[2] - values[1] - 1,
		103 - values[2]
	};
	return retVal;
}

// only viable for my input, it changes with different characteristics of different input.
int64_t isViable(std::vector<int> spoons)
{
	int a = spoons[0];
	int b = spoons[1];
	int c = spoons[2];
	int d = spoons[3];
	if (!b)
		return 0;

	if ((3 * a - 3 * b - c > 0) && (4 * c - 2 * d > 0) && (2 * d - 3 * a > 0))
	{
		return 1;
	}
	return 0;
}

Spoons generateSet()
{
	Spoons retVal;
	for (int i = 1; i <= 103; i++)
	{
		for (int j = 1; j <= 103; j++)
		{
			if (i == j)
				continue;
			for (int k = 1; k <= 103; k++)
			{
				if (k == j || k == i)
					continue;
				std::vector<int> spoons = generate(i, j, k);
				if (isViable(spoons))
					retVal.push_back(spoons);
			}
		}
	}
	return retVal;
}

template<class T>
int64_t score(const T& spoons)
{
	int64_t capacity = 0;
	int64_t durability = 0;
	int64_t flavor = 0;
	int64_t texture = 0;
	for (int i = 0; i < 4; i++)
	{
		int spoon = spoons[i];
		Characteristic ingr = ingrdedients[i];
		capacity += (spoon * ingr.Capacity);
		durability += (spoon * ingr.Durability);
		flavor += (spoon * ingr.Flavor);
		texture += (spoon * ingr.Texture);
	}
	return capacity*durability*flavor*texture;
}

int64_t getCalorieCount(std::vector<int> spoons)
{
	int64_t cal = 0;
	for (int i = 0; i < 4; i++)
	{
		int spoon = spoons[i];
		cal += (spoon * ingrdedients[i].Calories);
	}
	return cal;
}
Spoons main_set;

int64_t partOne()
{
	std::vector<int64_t> scores;
	for (auto& s : main_set)
	{
		int64_t scoree = score(s);
		scores.push_back(scoree);
	}
	std::sort(scores.begin(), scores.end(), std::greater<int64_t>());
	return scores[0];
}

int64_t partTwo()
{
	std::vector<int64_t> scores;
	for (auto& s : main_set)
	{
		int64_t scoree = score(s);
		if (getCalorieCount(s) == 500)
			scores.push_back(scoree);
	}
	std::sort(scores.begin(), scores.end(), std::greater<int64_t>());
	return scores[0];
}

int main()
{
	main_set = generateSet();
	std::cout << partOne() << std::endl;
	std::cout << partTwo();
}
