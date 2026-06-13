#pragma once

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

#define FOREVER 1

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

void	findSolution(const std::vector<int>& conditions);
void	printSolution(std::vector<std::vector<i64>>& colorLines, int nodes);

template <typename T>
void	printArray(const std::vector<T>& array)
{
	for (const T& it : array)
	{
		std::cout << it << " ";
	}
	std::cout << std::endl;
}