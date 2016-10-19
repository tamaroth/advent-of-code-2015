#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <chrono>
#include <string>
#include <vector>
#include <tuple>
#include <regex>
#include <map>

using std::chrono::high_resolution_clock;

enum class IDENT
{
	DAY01,
	DAY02,
	DAY03,
	DAY04,
	DAY05,
	DAY06,
	DAY07,
	DAY08,
	DAY09,
	DAY10,
	DAY11,
	DAY12,
	DAY13,
	DAY14,
	DAY15,
	DAY16,
	DAY17,
	DAY18,
	DAY19,
	DAY20,
	DAY21,
	DAY22,
	DAY23,
	DAY24,
	DAY25,
	ALLDAYS
};

class CAoC
{
public:
	CAoC() {};
	virtual ~CAoC() {}

	virtual
	void init() = 0;

	virtual
	std::string part_one() const = 0;

	virtual
	std::string part_two() const = 0;
};
