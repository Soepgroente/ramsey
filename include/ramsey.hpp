#pragma once

#include <array>
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

#include "Graph.hpp"

#define FOREVER 1
#define RESET "\033[0m"

constexpr std::array<const char*, 10> colorPrints = {"\033[34m", "\033[31m", "\033[32m", "\033[33m", "\033[30m", "\033[35m", "\033[35m", "\033[35m", "\033[35m", "\033[35m"};

typedef enum s_coloring
{
	BLANK,
	BLUE,
	RED,
	GREEN,
	YELLOW,
	BLACK,
	PINK
}	t_coloring;

typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint16_t ui16;
typedef uint32_t ui32;
typedef uint64_t ui64;

i64		binomial_coefficient(ui16 x, ui16 y);
i64		factorial(ui16 num);

std::vector<i64>	createLines(int nodes);
std::vector<i64>	allThePreColoring(const std::vector<i64>& lines, std::vector<std::vector<i64>>& coloredLines, std::vector<int> conditions, const int nodes);

i64		nodesInColor(const std::vector<i64>& coloredLines);
int		amountOfNodes(const i64* buffer, int bufferSize, i64 newLine);
bool	legalClusterSizes(const std::vector<int>& instances, const std::vector<i64>& coloredLines, i64 newLine, int maxClusterSize);
bool	legalClusterSizes2(const std::vector<i64>& coloredLines, i64 newLine, int maxClusterSize);
bool	checkSolution(const std::vector<std::vector<i64>>& coloredLines, const std::vector<int>& conditions);

void	findSolution(const Graph& graph);
void	printSolution(std::vector<std::vector<i64>>& coloredLines, int nodes);
void	printLine(i64 line);

constexpr std::array<int, 11> nodesInACluster =
{
	0,
	1 * (1 - 1) / 2,
	2 * (2 - 1) / 2,
	3 * (3 - 1) / 2,
	4 * (4 - 1) / 2,
	5 * (5 - 1) / 2,
	6 * (6 - 1) / 2,
	7 * (7 - 1) / 2,
	8 * (8 - 1) / 2,
	9 * (9 - 1) / 2,
	10 * (10 - 1) / 2
};

template <typename T>
void	printArray(const std::vector<T>& array)
{
	for (const T& it : array)
	{
		std::cout << it << " ";
	}
	std::cout << std::endl;
}