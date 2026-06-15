#include "ramsey.hpp"

std::vector<i64>	createLines(int nodes)
{
	std::vector<i64>	lines;

	lines.reserve(nodes * (nodes - 1) / 2);
	for (i32 i = 0; i < nodes - 1; i++)
	{
		for (i32 j = i + 1; j < nodes; j++)
		{
			lines.push_back(1ULL << i | 1ULL << j);
		}
	}
	std::sort(lines.begin(), lines.end());
	return lines;
}

std::vector<int>	getInput(char** argv)
{
	std::vector<int>	colors;

	for (int i = 1; argv[i] != nullptr; i++)
	{
		colors.push_back(std::stoi(argv[i]));
		if (colors.back() < 3 || colors.back() > 10)
		{
			throw std::invalid_argument("Arguments must be between 3-10.");
		}
	}
	if (colors.size() < 2 || colors.size() > 10)
	{
		throw std::invalid_argument("Error: Number of colors must be between 2 and 10.");
	}
	return colors;
}
