/************************************************************************/
/* Advent of Code:
/* Day 14: Knights of the Dinner Table
/************************************************************************/

#include <boost/algorithm/string.hpp>
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <tuple>
#include <map>

using Deer = std::tuple<std::string, int, int, int>;
std::vector<Deer> reindeers = {
	Deer("Rufolph",	22,	8,	165),
	Deer("Cupid",	8,	17,	114),
	Deer("Prancer",	18,	6,	103),
	Deer("Donner",	25,	6,	145),
	Deer("Dasher",	11,	12,	125),
	Deer("Comet",	21,	6,	121),
	Deer("Blitzen",	18,	3,	50),
	Deer("Vixen",	20,	4,	75),
	Deer("Dancer",	7,	20,	119)
};

int deerDistanceOverTime(Deer& deer, int time)
{
	int speed = std::get<1>(deer);
	int duration = std::get<2>(deer);
	int rest = std::get<3>(deer);
	int oneCycle = duration + rest;

	return (time / oneCycle * speed * duration) + (std::min(time % oneCycle, duration) * speed);
}

int partOne()
{
	std::vector<int> distances;

	for (auto& x : reindeers)
	{
		distances.push_back(deerDistanceOverTime(x, 2503));
	}
	std::sort(distances.begin(), distances.end(), std::greater<int>());
	return distances[0];
}

template<class A, class B>
std::pair<B, A> flipPair(const std::pair<A, B>& pair)
{
	return std::pair<B, A>(pair.second, pair.first);
}

template<class A, class B>
std::multimap<B, A, std::greater<int>> flipMap(const std::map<A, B>& src)
{
	std::multimap<B, A, std::greater<int>> dst;
	std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), flipPair<A, B>);
	return dst;
}

int partTwo()
{
	using Board = std::map<std::string, int>;
	using Results = std::multimap<int, std::string, std::greater<int>>;
	Board raceboard;
	Board scoreboard;
	for (int i = 1; i <= 2503; i++)
	{
		for (auto& r : reindeers)
		{
			raceboard[std::get<0>(r)] = deerDistanceOverTime(r, i);
		}
		Results reverseRaceboard = flipMap(raceboard);
		
		int highScore = 0;
		for (const auto& rr : reverseRaceboard)
		{
			if (rr.first >= highScore)
			{
				highScore = rr.first;
				if (scoreboard.find(rr.second) != scoreboard.end())
				{
					scoreboard[rr.second]++;
				}
				else
				{
					scoreboard[rr.second] = 1;
				}
			}
			else
			{
				break;
			}
		}
	}
	
	Results res = flipMap(scoreboard);
	return std::begin(res)->first;
}

int main()
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::cout << partOne() << std::endl;
	std::cout << partTwo() << std::endl;
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";
}
