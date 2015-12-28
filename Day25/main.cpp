#include <iostream>
#include <map>

int64_t partOne()
{
	int64_t count = 20151125;
	for (int x = 1; x != -1; x++)
	{
		int64_t j = 1;
		for (int64_t i = x; i >= 1; i--)
		{
			if (i == 2981 && j == 3075)
			{
				return count;
			}
			count = (count * 252533) % 33554393;
			j++;
		}
	}

	return -1;
}

int main()
{
	std::cout << "Part One: " << partOne() << std::endl;
}