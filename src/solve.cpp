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

/*	Two initial checks to save time: only check the lines that have at least 1 node connected to the newly added node.
	Then checks whether the total number of lines that are connected by at least 1 node is less than max size.	*/

static bool legalClusterSizes(const std::vector<i64>& coloredLines, i64 newLine, int maxClusterSize)
{
	const int numLines = maxClusterSize * (maxClusterSize - 1) / 2;

	if (static_cast<int>(coloredLines.size()) + 1 < numLines)
	{
		return true;
	}
	return enumerateCombinationsAndCheck(coloredLines, newLine, maxClusterSize, numLines);
}

static int	placableOptions(i64 line,
	const std::vector<std::vector<i64>>& coloredLines,
	const std::vector<int>& conditions,
	const std::vector<i64>& coloredNodes)
{
	int options = 0;

	for (size_t i = 0; i < conditions.size(); i++)
	{
		/*	If 0 or 1 nodes connect with the set of all nodes of that color, we can determine it's legal. 
			If both nodes connect, we call the expensive legalClusterSizes() function to check	*/

		if (__builtin_popcountll(coloredNodes[i] & line) == 2)
		{
			options |= (static_cast<int>(legalClusterSizes(coloredLines[i], line, conditions[i])) << i);
		}
		else
		{
			options |= (1 << i);
		}
	}
	return options;
}

static bool	attemptToSolve(GraphState& state, const std::vector<int>& conditions)
{
	/*	store all nodes hit by each color in a single i64 to calculate placable options more effectively	*/

	std::vector<i64>	coloredNodes(conditions.size());
	
	for (size_t i = 0; i < state.coloredLines.size(); i++)
	{
		for (i64 line : state.coloredLines[i])
		{
			coloredNodes[i] |= line;
		}
	}

	int changes = 1;

	while (changes > 0)
	{
		changes = 0;
		std::vector<i64>& lines = state.lines;

		for (size_t i = 0; i < lines.size(); i++)
		{
			int options = placableOptions(lines[i], state.coloredLines, conditions, coloredNodes);
			int count = __builtin_popcount(options);

			switch (count)
			{
				case 0:
					return false;
				case 1:
				{
					int color = __builtin_ctz(options);

					state.coloredLines[color].push_back(lines[i]);
					coloredNodes[color] |= lines[i];
					lines.erase(lines.begin() + i);
					changes++;
					i--;
					break;
				}
				default:
					break;
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

static std::vector<i64>	colorOuterCircle(const std::vector<i64>& lines, std::vector<i64>& coloredLines, int nodes)
{
	std::vector<i64> filteredLines;

	for (size_t i = 0; i < lines.size(); i++)
	{
		int node1 = __builtin_ctzll(lines[i]);
		int node2 = __builtin_ctzll(lines[i] ^ (1ULL << node1));
		if (std::abs(node1 - node2) == 1 || std::abs(node1 - node2) == nodes - 1)
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

static std::vector<i64>	colorInnerCircle(const std::vector<i64>& lines, std::vector<i64>& coloredLines, int nodes)
{
	std::vector<i64> filteredLines;

	for (size_t i = 0; i < lines.size(); i++)
	{
		int node1 = __builtin_ctzll(lines[i]);
		int node2 = __builtin_ctzll(lines[i] ^ (1ULL << node1));
		if (std::abs(node1 - node2) == 2 || ((node1 == 0 || node2 == 0) && std::abs(node1 - node2) == nodes - 2))
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
	int index = colors - 1;
	Stopwatch stopwatch;

	for (int totalNodes = 2; totalNodes <= 64; totalNodes++)
	{
		stopwatch.start();
		finalState.clear();

		std::vector<i64>	newLines = createLines(totalNodes);
		std::vector<std::vector<i64>>	clrs(colors);

		if (totalNodes > 3)
		{
			newLines = colorOuterCircle(newLines, clrs[0], totalNodes);
			newLines = colorInnerCircle(newLines, clrs[index], totalNodes);
		}

		if (recursiveSearch(GraphState(clrs, newLines), conditions) == true)
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
