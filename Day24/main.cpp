/************************************************************************/
/* Advent of Code:
/* Day 24: It Hangs in the Balance
/************************************************************************/

#include <algorithm>
#include <iostream>
#include <chrono>
#include <vector>

using Set = std::vector<int>;
Set input = { 1, 3, 5, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113 };

size_t		p1_lowest;
uint64_t	p1_qe;
int			p1_sum;
size_t		p2_lowest;
uint64_t	p2_qe;
int			p2_sum;

void findSum(Set numbers, Set partial)
{
	int s = 0;
	std::for_each(partial.begin(), partial.end(), [&](const int& element) {s += element; });
	if (s == p1_sum)
	{
		if (partial.size() <= p1_lowest)
		{
			p1_lowest = partial.size();
			uint64_t qe = 1;
			std::for_each(partial.begin(), partial.end(), [&](const int& element) {qe *= element; });
			p1_qe = std::min(p1_qe, qe);
		}
	}
	if (s == p2_sum)
	{
		if (partial.size() <= p2_lowest)
		{
			p2_lowest = partial.size();
			uint64_t qe = 1;
			std::for_each(partial.begin(), partial.end(), [&](const int& element) {qe *= element; });
			p2_qe = std::min(p2_qe, qe);
		}
	}
	if (s >= p1_sum && s >= p2_sum)
		return;
	int n;
	for (Set::const_iterator ai = numbers.begin(); ai != numbers.end(); ai++)
		{
		n = *ai;
		Set remaining;
		for (Set::const_iterator aj = ai; aj != numbers.end(); aj++)
		{
			if (aj == ai)continue;
			remaining.push_back(*aj);
		}
		Set partial_rec = partial;
		partial_rec.push_back(n);
		findSum(remaining, partial_rec);
	}
}

int main()
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	int sum = 0;
	p1_qe = p2_qe = 1;
	p1_lowest = p2_lowest = input.size();
	std::for_each(input.begin(), input.end(), [&sum](const int& element) {sum += element; p1_qe = p2_qe = p1_qe*element; });
	p1_sum = sum / 3;
	p2_sum = sum / 4;
	findSum(input, Set());
	std::cout << "Part One: " << p1_qe << std::endl;
	std::cout << "Part Two: " << p2_qe << std::endl;
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";
	return 0;
}
