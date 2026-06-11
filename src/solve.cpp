#include "ramsey.hpp"
#include "Stopwatch.hpp"

int totalLines;
int colors;

/*	Combines flipped bits of all lines into a single 64 bit integer, then compares the total amount of flipped bits to clusterSize.
	If the amount is equal to the clusterSize variable, every node is connected to every other node (so they're a cluster)	*/

static int amountOfNodes(const i64* buffer, int bufferSize, i64 newLine)
{
	for (int i = 0; i < bufferSize; i++)
	{
		newLine |= buffer[i];
	}
	return __builtin_popcountll(newLine);
}

static bool enumerateCombinationsAndCheck(const std::vector<i64>& inputArray, i64 newLine, int maxClusterSize, int numLines)
{
	const int	arraySize = static_cast<int>(inputArray.size());
	const int	bufferSize = numLines - 1;
	static int	indexes[16];
	static i64	buffer[16];

	int position;

	if (bufferSize <= 0 || arraySize < bufferSize)
	{
		return true;
	}
	if (maxClusterSize <= 2)
	{
		return false;
	}

	/*	Set indexes to lowest value, e.g. 0-1-2-3	*/

	for (int i = 0; i < bufferSize; i++)
	{
		indexes[i] = i;
		buffer[i] = inputArray[indexes[i]];
	}
	/*	input numbers associated with indexes into buffer, check whether they're clustered, advance indexes	*/
	
	while (true)
	{
		if (amountOfNodes(buffer, bufferSize, newLine) == maxClusterSize)
		{
			return false;
		}
		position = bufferSize - 1;
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
			buffer[i] = inputArray[indexes[i]];
		}
	}
	return true;
}

/*	Two initial checks to save time: only check the lines that have at least 1 node connected to the newly added node.
	Then checks whether the total number of lines that are connected by at least 1 node is less than max size.	*/

static bool legalClusterSizes(const std::vector<i64>& colorLines, i64 newLine, int maxClusterSize)
{
	int numLines = maxClusterSize * (maxClusterSize - 1) / 2;

	if (static_cast<int>(colorLines.size()) + 1 < numLines)
	{
		return true;
	}
	return enumerateCombinationsAndCheck(colorLines, newLine, maxClusterSize, numLines);
}

static bool	recursiveSearch(
	std::vector<std::vector<i64>>& colorLines,
	const std::vector<i64>& lines,
	const std::vector<int>& conditions,
	int lineIndex)
{
	if (lineIndex < totalLines)
	{
		for (int j = 0; j < colors; j++)
		{
			if (legalClusterSizes(colorLines[j], lines[lineIndex], conditions[j]) == true)
			{
				colorLines[j].push_back(lines[lineIndex]);
				if (recursiveSearch(colorLines, lines, conditions, lineIndex + 1) == true)
				{
					return true;
				}
				colorLines[j].pop_back();
			}
		}
		return false;
	}
	return true;
}

void	findSolution(const std::vector<int>& conditions)
{
	colors = conditions.size();
	Stopwatch stopwatch;

	for (int totalNodes = 2; totalNodes <= 64; totalNodes++)
	{
		stopwatch.start();

		std::vector<i64>	lines = createLines(totalNodes);
		totalLines = lines.size();
		std::vector<std::vector<i64>>	colorLines(colors);

		// for (int i = 0; i < totalNodes - 1; i++)
		// {
		// 	colorLines[0].push_back(1ULL << i | 1ULL << (i + 1));
		// }
		// if (recursiveSearch(colorLines, lines, conditions, totalNodes - 1) == true)
		if (recursiveSearch(colorLines, lines, conditions, 0) == true)
		{
			stopwatch.stop();
			std::cout << "Solution found for " << totalNodes << " nodes in " << stopwatch << std::endl;
			printSolution(colorLines, lines, totalNodes);
		}
		else
		{
			stopwatch.stop();
			std::cout << "Success! No solution found for " << totalNodes << " nodes. Took " << stopwatch << std::endl;
			return;
		}
		stopwatch.reset();
	}
}
