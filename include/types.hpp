#pragma once

#include <cstdlib>

typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint16_t ui16;
typedef uint32_t ui32;
typedef uint64_t ui64;

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