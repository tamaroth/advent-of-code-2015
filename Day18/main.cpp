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
int countNeighboursOn(Grid<S>& grid, int x, int y, bool partTwo = false)
{
	int lightsOn = 0;
	if (x == 0) // top row
	{
		if (y == 0) // top left
		{
			if (partTwo)
				return 3;
			lightsOn = isLightOn(grid[0][1]) + isLightOn(grid[1][0]) + isLightOn(grid[1][1]);
		}
		else if (y == grid[0].size()-1) // top right
		{
			if (partTwo)
				return 3;
			lightsOn = isLightOn(grid[0][y - 1]) + isLightOn(grid[1][y]) + isLightOn(grid[1][y - 1]);
		}
		else // rest of top row
		{
			lightsOn = isLightOn(grid[0][y - 1]) + isLightOn(grid[0][y + 1]) + \
				isLightOn(grid[1][y - 1]) + isLightOn(grid[1][y]) + isLightOn(grid[1][y + 1]);
		}
	}
	else if (x == grid.size() - 1) // bottom row
	{
		if (y == 0)	// bottom left
		{
			if (partTwo)
				return 3;
			lightsOn = isLightOn(grid[x - 1][0]) + isLightOn(grid[x][1]) + isLightOn(grid[x - 1][1]);
		}
		else if (y == grid[x].size() - 1) // bottom right
		{
			if (partTwo)
				return 3;
			lightsOn = isLightOn(grid[x - 1][y]) + isLightOn(grid[x - 1][y - 1]) + isLightOn(grid[x][y - 1]);
		}
		else // rest of bottom row
		{
			lightsOn = isLightOn(grid[x][y - 1]) + isLightOn(grid[x][y + 1]) + \
				isLightOn(grid[x - 1][y - 1]) + isLightOn(grid[x - 1][y]) + isLightOn(grid[x - 1][y + 1]);
		}
	}
	else if (y == 0) // left column
	{
		lightsOn =	isLightOn(grid[x - 1][0]) + isLightOn(grid[x - 1][1]) + \
					isLightOn(grid[x][1]) + \
					isLightOn(grid[x + 1][0]) + isLightOn(grid[x + 1][1]);
	}
	else if (y == grid.size() -1) // right column
	{
		lightsOn =	isLightOn(grid[x - 1][y - 1]) + isLightOn(grid[x - 1][y]) + \
					isLightOn(grid[x][y - 1]) + \
					isLightOn(grid[x + 1][y - 1]) + isLightOn(grid[x + 1][y]);
	}
	else
	{
		lightsOn = isLightOn(grid[x - 1][y - 1]) + isLightOn(grid[x - 1][y]) + isLightOn(grid[x - 1][y + 1]) + \
			isLightOn(grid[x][y - 1]) + isLightOn(grid[x][y + 1]) + \
			isLightOn(grid[x + 1][y - 1]) + isLightOn(grid[x + 1][y]) + isLightOn(grid[x + 1][y + 1]);
	}
	return lightsOn;
}

template<int S>
Grid<S> animate(Grid<S>& grid, bool partTwo = false)
{
	Grid<S> newGrid = grid;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid.size(); j++)
		{
			if (isLightOn(grid[i][j]))
			{
				if (countNeighboursOn(grid, i, j, partTwo) != 2 && countNeighboursOn(grid, i, j, partTwo) != 3)
					newGrid[i][j] = '.';
			}
			else
			{
				if (countNeighboursOn(grid, i, j, partTwo) == 3)
					newGrid[i][j] = '#';
			}
		}
	}
	return newGrid;
}

template<int S>
void lightCorners(Grid<S>& grid)
{
	grid[0][0] = '#';
	grid[0][(int)grid[0].size() - 1] = '#';
	grid[(int)grid.size() - 1][0] = '#';
	grid[(int)grid.size() - 1][(int)grid[0].size() - 1] = '#';
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
	for (int i = 0; i < grid.size(); i++)
	{
		grid = animate(grid);
	}
	return countLights(grid);
}

template<int S>
int partTwo(Grid<S> grid)
{
	for (int i = 0; i < grid.size(); i++)
	{
		lightCorners(grid);
		grid = animate(grid, true);
	}
	return countLights(grid);
	return 1;
}

template<int S>
Grid<S> readGrid()
{
	std::ifstream infile("data_d18.txt");
	std::string input;
	Grid<S> grid;
	int i = 0;

	while (std::getline(infile, input))
	{
		int j = 0;
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
	Grid<100> grid = readGrid<100>();
	std::cout << partOne(grid) << std::endl;
	std::cout << partTwo(grid) << std::endl;
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";
}
