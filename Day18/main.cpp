/************************************************************************/
/* Advent of Code:
/* Day 18: Like a GIF For Your Yard
/************************************************************************/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <array>

template<int S>
using Grid = std::array<std::array<char, S>, S>;

int isLightOn(char ch)
{
	if (ch == '#')
		return 1;
	return 0;
}

template<int S>
int neighboursOn(Grid<S>& grid, int x, int y)
{
	return isLightOn(grid[x - 1][y - 1]) + isLightOn(grid[x - 1][y]) + isLightOn(grid[x - 1][y + 1]) + \
		isLightOn(grid[x][y - 1]) + isLightOn(grid[x][y + 1]) + \
		isLightOn(grid[x + 1][y - 1]) + isLightOn(grid[x + 1][y]) + isLightOn(grid[x + 1][y + 1]);
}

template<int S>
Grid<S> animate(Grid<S>& grid)
{
	Grid<S> newGrid = grid;
	for (int i = 1; i < S - 1; i++)
	{
		for (int j = 1; j < S - 1; j++)
		{
			if (isLightOn(grid[i][j]))
			{
				if (neighboursOn(grid, i, j) != 2 && neighboursOn(grid, i, j) != 3)
					newGrid[i][j] = '.';
			}
			else
			{
				if (neighboursOn(grid, i, j) == 3)
					newGrid[i][j] = '#';
			}
		}
	}
	return newGrid;
}

template<int S>
void lightCorners(Grid<S>& grid)
{
	grid[1][1] = '#';
	grid[1][S - 2] = '#';
	grid[S - 2][1] = '#';
	grid[S - 2][S - 2] = '#';
}

template<int S>
int countLights(Grid<S>& grid)
{
	int lights = 0;
	for (auto row : grid)
	{
		for (auto element : row)
		{
			if (element == '#')
				lights++;
		}
	}
	return lights;
}

template<int S>
int partOne(Grid<S> grid)
{
	for (int i = 0; i < 100; i++)
	{
		grid = animate(grid);
	}
	return countLights(grid);
}

template<int S>
int partTwo(Grid<S> grid)
{
	for (int i = 0; i < 100; i++)
	{
		lightCorners(grid);
		grid = animate(grid);
	}
	lightCorners(grid);
	return countLights(grid);
}

template<int S>
void setGrid(Grid<S>& grid, char val)
{
	for (auto& row : grid)
	{
		for (auto& element : row)
		{
			element = val;
		}
	}
}

template<int S>
Grid<S> readGrid()
{
	std::ifstream infile("data_d18.txt");
	std::string input;
	Grid<S> grid;
	int i = 1;

	setGrid<S>(grid, '.');
	while (std::getline(infile, input))
	{
		int j = 1;
		for (const auto& ch : input)
		{
			if (i > S || j > S)
				return grid;
			grid[i][j++] = ch;
		}
		i++;
	}
	return grid;
}

int main()
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	Grid<102> grid = readGrid<102>();
	std::cout << partOne(grid) << std::endl;
	std::cout << partTwo(grid) << std::endl;
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";
}
