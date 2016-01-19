/************************************************************************/
/* Advent of Code:
/* Day 13: Knights of the Dinner Table
/************************************************************************/

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <tuple>
#include <map>

using namespace std;
using CData = map<tuple<string, string>, int>;
CData input;
vector<string> names;

vector<string> split(string const& inStr, string const& delim)
{
	std::vector<std::string> retVal;
	boost::split(retVal, inStr, boost::is_any_of(delim));
	return retVal;
}

void readInputData()
{
	ifstream infile("data_d13.txt");
	string line;

	while (getline(infile, line))
	{
		line.replace(line.find("."), 1, "");
		vector<string> data = split(line, " ");
		if (none_of(names.begin(), names.end(), [&](const string& str) { return str == data[0]; }))
			names.push_back(data[0]);
		input[make_tuple(data[0], data[10])] = data[2] == "lose" ? 0 - stoi(data[3]) : stoi(data[3]);
	}
}

int countHappiness(vector<string>& inData)
{
	int happiness = 0;

	for (size_t i = 0; i < inData.size(); i++)
	{
		happiness += (input[make_tuple(inData[i], inData[(i + 1) % inData.size()])] + input[make_tuple(inData[(i + 1) % inData.size()], inData[i])]);
	}

	return happiness;
}

int partOne()
{
	vector<int> happiness;
	do
	{
		happiness.push_back(countHappiness(names));
	} while (next_permutation(names.begin(), names.end()));
	sort(happiness.begin(), happiness.end());
	return happiness[happiness.size() - 1];
}

int partTwo()
{
	for (const auto x : names)
	{
		input[make_tuple(x, "tamaroth")] = 0;
		input[make_tuple("tamaroth", x)] = 0;
	}

	names.push_back("tamaroth");

	vector<int> happiness;
	do
	{
		happiness.push_back(countHappiness(names));
	} while (next_permutation(names.begin(), names.end()));
	sort(happiness.begin(), happiness.end());
	return happiness[happiness.size() - 1];
}

int main()
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	readInputData();
	std::cout << partOne() << std::endl;
	std::cout << partTwo() << std::endl;
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";
}
