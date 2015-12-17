/************************************************************************/
/* Advent of Code:
/* Day 17: No Such Thing as Too Much
/************************************************************************/

#include <algorithm>
#include <iostream>
#include <chrono>
#include <list>
#include <vector>

using Set = std::vector<int>;
using Subsets = std::vector<Set>;

Subsets getAllSubsets(Set set)
{
	Subsets subset;
	Set empty;
	subset.push_back(empty);

	for (int i = 0; i < set.size(); i++)
	{
		Subsets subsetTemp = subset;

		for (int j = 0; j < subsetTemp.size(); j++)
			subsetTemp[j].push_back(set[i]);

		for (int j = 0; j < subsetTemp.size(); j++)
			subset.push_back(subsetTemp[j]);
	}
	return subset;
}

int partOne(Subsets& subsets)
{
	int numberOfCombinations = 0;

	for (const auto& a : subsets)
	{
		int sum = 0;
		std::for_each(a.begin(), a.end(), [&](int n) { sum += n; });
		if (sum == 150)
		{
			numberOfCombinations++;
		}
	}
	return numberOfCombinations;
}

// Could be integrated into partOne for speed reasons, but for the sake of consistency I'll keep it separate.
int partTwo(Subsets& subsets)
{
	Subsets correctSubsets;

	for (const auto& a : subsets)
	{
		int sum = 0;
		std::for_each(a.begin(), a.end(), [&](int n) { sum += n; });
		if (sum == 150)
		{
			correctSubsets.push_back(a);
		}
	}
	std::sort(correctSubsets.begin(), correctSubsets.end(), [](const Set& a, const Set& b) { return a.size() < b.size(); });
	int numberOfLowest = 0;
	for (const auto& s : correctSubsets)
	{
		if (s.size() == correctSubsets[0].size())
		{
			numberOfLowest++;
			continue;
		}
		break;
	}
	return numberOfLowest;
}

Subsets generateSubsets()
{
	Set set = { 33, 14, 18, 20, 45, 35, 16, 35, 1, 13, 18, 13, 50, 44, 48, 6, 24, 41, 30, 42 }; // puzzle input
	Subsets subsets = getAllSubsets(set);
	return subsets;
}

int main()
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	Subsets subsets = generateSubsets();
	std::cout << partOne(subsets) << std::endl;
	std::cout << partTwo(subsets) << std::endl;
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";
}
