#pragma once

#include <array>
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cstdbool>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

#include "types.hpp"

#define FOREVER 1
#define RESET "\033[0m"

class Graph;
class MonoGraph;

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

void	findSolution(Graph& graph, const std::vector<int>& conditions);
bool	checkSolution(std::vector<MonoGraph>& colors);
void	printSolution(std::vector<std::vector<i64>>& coloredLines, int nodes);
std::ostream&	printLine(i64 line, std::ostream& os);

template <typename T>
void	printArray(const std::vector<T>& array)
{
	for (const T& it : array)
	{
		std::cout << it << " ";
	}
	std::cout << std::endl;
}