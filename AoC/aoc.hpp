#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <regex>
#include <map>

using std::chrono::high_resolution_clock;

enum class IDENT
{
	DAY01,
	DAY02,
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
