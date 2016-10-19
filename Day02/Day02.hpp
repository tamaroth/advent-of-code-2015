#pragma once

#include "../AoC/aoc.hpp"

class CDay02 :
	public CAoC
{
public:
	CDay02();
	~CDay02();

	virtual
		void init() override;

	virtual
		std::string part_one() const override;

	virtual
		std::string part_two() const override;

	using Size = std::vector<uint32_t>;
	using Sizes = std::vector<Size>;

private:
	uint32_t getBoxArea(const Size& box) const;
	uint32_t getSmallestSideArea(Size box) const;
	uint32_t getRibbonLength(Size box) const;

	Sizes m_sizes;
};

