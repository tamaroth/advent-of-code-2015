#pragma once
#include "../AoC/aoc.hpp"

extern "C" {
	#include "md5.h"
}

class CDay04 :
	public CAoC
{
public:
	CDay04();
	~CDay04();

	virtual
		void init() override;

	virtual
		std::string part_one() const override;

	virtual
		std::string part_two() const override;

private:
	std::string		m_input{ "bgvyzdsv" };
};
