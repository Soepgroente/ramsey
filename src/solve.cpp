#include <iostream>
#include <csignal>
#include "ramsey.hpp"
#include "Stopwatch.hpp"
#include "GraphState.hpp"

int colors;
GraphState	finalState;

/*
	Before checking every combination (expensive), this function checks whether:
	- both nodes of the new line overlap with the already colored set
	- the total amount of nodes in the colored set + the new line is less than the max cluster size
	- the total amount of lines required to create a full cluster is less than the binomial coefficient of maxClusterSize (n * (n - 1) / 2)

	in hopes of an early exit
*/

static int	placableOptions(
	i64 line,
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
		coloredNodes[i] = nodesInColor(state.coloredLines[i]);
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



void	findSolution(const std::vector<int>& conditions)
{
	std::signal(SIGINT, [](int signum)
	{
		std::cout << "\nInterrupt signal (" << signum << ") received. Exiting..." << std::endl;
		std::exit(signum);
	});

	colors = static_cast<int>(conditions.size());
	Stopwatch stopwatch;
	Stopwatch totalStopwatch;

	for (int totalNodes = 2; totalNodes <= 64; totalNodes++)
	{
		totalStopwatch.start();
		std::cout << "========================Trying " << totalNodes << " nodes========================" << std::endl;
		stopwatch.start();
		finalState.clear();

		std::vector<i64>	newLines = createLines(totalNodes);
		std::vector<std::vector<i64>>	clrs(colors);

		/*	If the amount of nodes == 3, coloring 0-1 1-2 and 2-0 would form a cluster of size 3.
			For higher values, the outer ring only forms clusters of size 2.	*/

		if (totalNodes > 3)
		{
			newLines = allThePreColoring(newLines, clrs, conditions, totalNodes);
		}

		if (recursiveSearch(GraphState(clrs, newLines), conditions) == true)
		{
			stopwatch.stop();
			if (totalNodes > 3 && checkSolution(finalState.coloredLines, conditions) == false)
			{
				std::cerr << "Error: solution found but does not satisfy conditions" << std::endl;
			}
			std::cout << "Solution found! " << stopwatch << std::endl;
			printSolution(finalState.coloredLines, totalNodes);
		}
		else
		{
			stopwatch.stop();
			totalStopwatch.stop();
			std::cout << "Success! No solution found for " << totalNodes << " nodes.\n" << stopwatch << ".\nTotal: " << totalStopwatch << std::endl;
			return;
		}
		stopwatch.reset();
	}
}
