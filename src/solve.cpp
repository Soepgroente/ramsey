#include <iostream>
#include <csignal>
#include "ramsey.hpp"
#include "Stopwatch.hpp"
#include "GraphState.hpp"

int colors;
GraphState	finalState;

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

static bool legalClusterSizes(const std::vector<i64>& coloredLines, i64 newLine, int maxClusterSize)
{
	int numLines = maxClusterSize * (maxClusterSize - 1) / 2;

	if (static_cast<int>(coloredLines.size()) + 1 < numLines)
	{
		return true;
	}
	return enumerateCombinationsAndCheck(coloredLines, newLine, maxClusterSize, numLines);
}

static int	placableOptions(i64 line, const std::vector<std::vector<i64>>& coloredLines, const std::vector<int>& conditions)
{
	int options = 0;

	for (size_t i = 0; i < conditions.size(); i++)
	{
		options |= (static_cast<int>(legalClusterSizes(coloredLines[i], line, conditions[i])) << i);
	}
	return options;
}

static bool	attemptToSolve(GraphState& state, const std::vector<int>& conditions)
{
	int changes = 1;

	while (changes > 0)
	{
		changes = 0;
		std::vector<i64>& lines = state.lines;
		for (size_t i = 0; i < lines.size(); i++)
		{
			int options = placableOptions(lines[i], state.coloredLines, conditions);
			int count = __builtin_popcount(options);
			if (count == 0)
			{
				return false;
			}
			else if (count == 1)
			{
				int color = __builtin_ctz(options);

				state.coloredLines[color].push_back(lines[i]);
				lines.erase(lines.begin() + i);
				changes++;
				i--;
			}
		}
	}
	return true;
}

static bool recursiveSearch(GraphState state, const std::vector<int>& conditions)
{
	if (state.lines.empty())
	{
		finalState = state;
		return true;
	}
	
	i64 line = state.lines[0];
	state.lines.erase(state.lines.begin());

	for (int i = 0; i < colors; i++)
	{
		if (legalClusterSizes(state.coloredLines[i], line, conditions[i]) == true)
		{
			state.coloredLines[i].push_back(line);
			GraphState backupState = state;
			if (attemptToSolve(state, conditions) == true)
			{
				if (recursiveSearch(state, conditions) == true)
				{
					return true;
				}
			}
			state = backupState;
			state.coloredLines[i].pop_back();
		}
	}
	return false;
}

static std::vector<i64>	filterLines(const std::vector<i64>& lines, std::vector<i64>& coloredLines)
{
	std::vector<i64> filteredLines;

	for (size_t i = 0; i < lines.size(); i++)
	{
		int node1 = __builtin_ctzll(lines[i]);
		int node2 = __builtin_ctzll(lines[i] ^ (1ULL << node1));
		if (std::abs(node1 - node2) == 1)
		{
			coloredLines.push_back(lines[i]);
		}
		else
		{
			filteredLines.push_back(lines[i]);
		}
	}
	return filteredLines;
}

void	findSolution(const std::vector<int>& conditions)
{
	std::signal(SIGINT, [](int signum)
	{
		std::cout << "\nInterrupt signal (" << signum << ") received. Exiting..." << std::endl;
		std::exit(signum);
	});
	colors = static_cast<int>(conditions.size());
	Stopwatch stopwatch;
	int largestConditionIndex = std::distance(conditions.begin(), std::max_element(conditions.begin(), conditions.end()));

	for (int totalNodes = 2; totalNodes <= 64; totalNodes++)
	{
		stopwatch.start();
		finalState.clear();

		std::vector<i64>	newLines = createLines(totalNodes);
		std::vector<std::vector<i64>>	clrs(colors);

		newLines = filterLines(newLines, clrs[largestConditionIndex]);

		assert(newLines.size() + clrs[largestConditionIndex].size() == static_cast<size_t>(totalNodes * (totalNodes - 1) / 2));

		if (recursiveSearch(GraphState(clrs, newLines), conditions))
		{
			stopwatch.stop();
			std::cout << "Solution found for " << totalNodes << " nodes in " << stopwatch << std::endl;
			printSolution(finalState.coloredLines, totalNodes);
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
