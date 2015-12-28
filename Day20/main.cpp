/************************************************************************/
/* Advent of Code:
/* Day 20: Infinite Elves and Infinite Houses
/************************************************************************/

#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <map>

std::vector<int64_t> findAllDivisors(int64_t n)
{
	std::vector<int64_t> divisors = { 1,n };
	int64_t end = static_cast<int64_t>(sqrt(n));

	for (int64_t i = 2; i <= end; i++)
	{
		if (n % i == 0)
		{
			divisors.push_back(i);
			if (end != i)
				divisors.push_back(n / i);
		}
	}
	return divisors;
}

int64_t partOne()
{
	int64_t x = 1;
	for (;;)
	{
		int64_t sum = 0;
		x++;
		std::vector<int64_t> divisors = findAllDivisors(x);
		std::for_each(divisors.begin(), divisors.end(), [&](const int64_t& elem) {sum += elem * 10; });
		if (sum >= 33100000)
			break;
	}
	return x;
}

int64_t partTwo()
{
	int64_t x = 0;

	for (;;)
	{
		int64_t sum = 0;
		x++;
		std::vector<int64_t> divisors = findAllDivisors(x);

		std::for_each(divisors.begin(), divisors.end(), [&](const int64_t& elem) {\
			if (elem*50 >= x)\
				sum += (elem*11);\
		});
		if (sum >= 33100000)
			break;
	}
	return x;
}

int main()
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::cout << "Part One: " << partOne() << std::endl;
	std::cout << "Part Two: " << partTwo() << std::endl;
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";
}
