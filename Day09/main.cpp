/************************************************************************/
/* Advent of Code:
/* Day 9: All in a Single Night
/************************************************************************/

#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <map>

class CTSP {
public:
	CTSP();
	~CTSP() {};

public:
	uint64_t partOne() { return getLo(m_distances); };
	uint64_t partTwo() { return getHi(m_distances); };

public:
	enum Cities
	{
		FAERUN,
		NORRATH,
		TRISTRAM,
		ALPHACENTAURI,
		ARBRE,
		SNOWDIN,
		TAMBI,
		STRAYLIGHT
	};

private:
	std::vector<std::string> split(std::string const& inStr, std::string const& delim);
	Cities str2City(std::string city);
	size_t getDistance(std::array<int, 8>& table);
	size_t computeLength();

	template<typename T>
	inline const typename T::key_type& getLo(const T& pMap) {
		return pMap.begin()->first;
	};
	template<typename T>
	inline const typename T::key_type& getHi(const T& pMap) {
		return pMap.rbegin()->first;
	};

private:
	std::array<std::array<int, 8>, 8>	m_cities;
	std::map<uint64_t, std::array<int, 8>> m_distances;
};

CTSP::CTSP()
{
	std::ifstream infile("data_d09.txt");
	std::string input;

	while (std::getline(infile, input))
	{
		std::vector<std::string> line = split(input, " ");
		m_cities[str2City(line[0])][str2City(line[2])] = std::stoi(line[4]);
		m_cities[str2City(line[2])][str2City(line[0])] = std::stoi(line[4]);
	}
	computeLength();
}

std::vector<std::string> CTSP::split(std::string const& inStr, std::string const& delim)
{
	std::vector<std::string> retVal;
	boost::split(retVal, inStr, boost::is_any_of(delim));
	return retVal;
}

CTSP::Cities CTSP::str2City(std::string city)
{
	std::array<std::string, 8> cityList = { "Faerun", "Norrath", "Tristram", "AlphaCentauri", "Arbre", "Snowdin", "Tambi", "Straylight" };
	auto p = std::find_if(cityList.begin(), cityList.end(), [&](std::string s) -> bool { return (s == city); });
	auto a = p - cityList.begin();
	return static_cast<CTSP::Cities>(a);
}

size_t CTSP::getDistance(std::array<int, 8>& table)
{
	uint64_t sum = 0;
	for (int i = 0; i < 7; i++)
	{
		sum += m_cities[table[i]][table[i + 1]];
	}
	return sum;
}

size_t CTSP::computeLength()
{
	std::array<int, 8> city = { FAERUN, NORRATH, TRISTRAM, ALPHACENTAURI, ARBRE, SNOWDIN, TAMBI, STRAYLIGHT };
	do
	{
		m_distances[getDistance(city)] = city;
	} while (std::next_permutation(city.begin(), city.end()));
	return 0;
}

int main()
{
	CTSP tsp;
	std::cout << tsp.partOne() << std::endl << tsp.partTwo();
}
