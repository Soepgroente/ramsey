#include "ramsey.hpp"

static std::vector<i64>	preColor(const std::vector<i64>& lines, std::vector<i64>& coloredLines, const int diff, const int nodes)
{
	// (void)nodes;
	std::vector<i64> uncoloredLines{};

	for (i64 line : lines)
	{
		int node1 = __builtin_ctzll(line);
		int node2 = __builtin_ctzll(line ^ (1ULL << node1));
		if (std::abs(node1 - node2) == diff ||
			(node1 == 0 && node2 == nodes - diff))
		{
			coloredLines.push_back(line);
		}
		else
		{
			uncoloredLines.push_back(line);
		}
	}
	return uncoloredLines;
}

/* static int	nextPreColor(const std::vector<int>& conditions, int prevIndex)
{
	const int size = static_cast<int>(conditions.size());

	if (prevIndex == size - 1)
	{
		prevIndex = -1;
	}
	for (int i = prevIndex + 1; i < size; i++)
	{
		if (conditions[i] > 0)
		{
			return i;
		}
	}
	return -1;
} */

std::vector<i64>	allThePreColoring(const std::vector<i64>& lines, std::vector<std::vector<i64>>& coloredLines, std::vector<int> conditions, const int nodes)
{
	std::vector<i64> uncoloredLines = lines;
	int colors = static_cast<int>(conditions.size());

	(void)colors;
	(void)nodes;
	// for (int i = 0; i < colors; i++)
	// {
	// 	conditions[i] -= 2;
	// }
	int diff = 1;
	// int index = static_cast<int>(conditions.size()) - 1;

	// while (index != -1 && diff < nodes - 1)
	// {
	// 	std::cout << "(pre)Index of precoloring: " << index << ", value: " << conditions[index] << " diff: " << diff << std::endl;
	// 	uncoloredLines = preColor(uncoloredLines, coloredLines[index], diff, nodes);
	// 	diff++;
	// 	conditions[index]--;
	// 	index = nextPreColor(conditions, index);
	// 	std::cout << "(post)Index of precoloring: " << index << ", value: " << conditions[index] << " diff: " << diff << std::endl;
	// }
	// for (int i = 0; i < colors; i++)
	// {
	// 	uncoloredLines = preColor(uncoloredLines, coloredLines[i], i + 1, nodes);
	// }
	for (int i = 0; i < 1; i++)
	{
		uncoloredLines = preColor(uncoloredLines, coloredLines[i], diff, nodes);
		diff++;
	}
	return uncoloredLines;
}

	// for (int i = 0; i < colors; i++)
	// {
	// 	std::cout << "Pre-colored " << coloredLines[i].size() << " with " << colorPrints[i] << "color" << RESET << std::endl;
	// 	printArray(coloredLines[i]);
	// }
	// std::cout << "Remaining uncolored lines: " << uncoloredLines.size() << std::endl;
	// printArray(uncoloredLines);