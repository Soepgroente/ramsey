#include "ramsey.hpp"

int amountOfNodes(const i64* buffer, int bufferSize, i64 newLine)
{
	for (int i = 0; i < bufferSize; i++)
	{
		newLine |= buffer[i];
	}
	return __builtin_popcountll(newLine);
}

i64	nodesInColor(const std::vector<i64>& coloredLines)
{
	i64 nodes = 0;
	for (i64 line : coloredLines)
	{
		nodes |= line;
	}
	return nodes;
}

/*	Combines flipped bits of all lines into a single 64 bit integer, then compares the total amount of flipped bits to clusterSize.
	If the amount is equal to the clusterSize variable, every node is connected to every other node (so they're a cluster)	*/

static bool enumerateCombinationsAndCheck(const std::vector<i64>& coloredLines, i64 newLine, int maxClusterSize, int numLines)
{
	const int	arraySize = static_cast<int>(coloredLines.size());
	const int	bufferSize = numLines - 1;
	static int	indexes[16];
	static i64	buffer[16];

	/*	Set indexes to lowest value, e.g. 0-1-2-3	*/

	for (int i = 0; i < bufferSize; i++)
	{
		indexes[i] = i;
		buffer[i] = coloredLines[i];
	}
	/*	input numbers associated with indexes into buffer, check whether they're clustered, advance indexes	*/
	
	while (true)
	{
		if (amountOfNodes(buffer, bufferSize, newLine) == maxClusterSize)
		{
			return false;
		}
		int position = bufferSize - 1;
		while (position >= 0 && indexes[position] == arraySize - bufferSize + position)
		{
			position--;
		}
		if (position < 0)
		{
			break;
		}
		indexes[position]++;
		for (int i = position + 1; i < bufferSize; i++)
		{
			indexes[i] = indexes[i - 1] + 1;
		}
		for (int i = position; i < bufferSize; i++)
		{
			buffer[i] = coloredLines[indexes[i]];
		}
	}
	return true;
}

bool legalClusterSizes(const std::vector<i64>& coloredLines, i64 newLine, int maxClusterSize)
{
	const int numLines = nodesInACluster[maxClusterSize];
	i64 nodes = nodesInColor(coloredLines);

	if (__builtin_popcountll(nodes & newLine) <= 1 ||
		__builtin_popcountll(nodes | newLine) < maxClusterSize ||
		static_cast<int>(coloredLines.size()) + 1 < numLines)
	{
		return true;
	}
	return enumerateCombinationsAndCheck(coloredLines, newLine, maxClusterSize, numLines);
}

bool	checkSolution(const std::vector<std::vector<i64>>& coloredLines, const std::vector<int>& conditions)
{
	for (size_t i = 0; i < coloredLines.size(); i++)
	{
		if (static_cast<int>(coloredLines[i].size()) < nodesInACluster[conditions[i]])
		{
			continue;
		}
		std::vector<i64> lines = coloredLines[i];
		for (size_t j = 0; j < coloredLines[i].size(); j++)
		{
			i64 testLine = lines[j];
			lines.erase(lines.begin() + j);
			if (legalClusterSizes(lines, testLine, conditions[i]) == false)
			{
				printLine(testLine);
				std::cerr << "Cluster of size " << conditions[i] << " found in" << colorPrints[i] << " color " << RESET << std::endl;
				return false;
			}
			lines.insert(lines.begin() + j, testLine);
		}
	}
	return true;
}
