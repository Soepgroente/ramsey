#include <iostream>
#include <csignal>
#include "ramsey.hpp"
#include "MonoGraph.hpp"
#include "Stopwatch.hpp"
#include "Graph.hpp"

/*
	Before checking every combination (expensive), this function checks whether:
	- both nodes of the new line overlap with the already colored set
	- the total amount of nodes in the colored set + the new line is less than the max cluster size
	- the total amount of lines required to create a full cluster is less than the binomial coefficient of maxClusterSize (n * (n - 1) / 2)

	in hopes of an early exit
*/

// static int	placableOptions(
// 	i64 line,
// 	const std::vector<std::vector<i64>>& coloredLines,
// 	const std::vector<int>& conditions,
// 	const std::vector<i64>& coloredNodes)
// {
// 	int options = 0;

// 	for (size_t i = 0; i < conditions.size(); i++)
// 	{
// 		/*	If 0 or 1 nodes connect with the set of all nodes of that color, we can determine it's legal. 
// 			If both nodes connect, we call the expensive legalClusterSizes() function to check	*/

// 		if (__builtin_popcountll(coloredNodes[i] & line) == 2)
// 		{
// 			options |= (static_cast<int>(legalClusterSizes2(coloredLines[i], line, conditions[i])) << i);
// 		}
// 		else
// 		{
// 			options |= (1 << i);
// 		}
// 	}
// 	return options;
// }

// static bool	attemptToSolve(GraphState& state, const std::vector<int>& conditions)
// {
// 	/*	store all nodes hit by each color in a single i64 to calculate placable options more effectively	*/

// 	std::vector<i64>	coloredNodes(conditions.size());
	
// 	for (size_t i = 0; i < state.coloredLines.size(); i++)
// 	{
// 		coloredNodes[i] = nodesInColor(state.coloredLines[i]);
// 	}

// 	int changes = 1;

// 	while (changes > 0)
// 	{
// 		changes = 0;
// 		std::vector<i64>& lines = state.lines;

// 		for (size_t i = 0; i < lines.size(); i++)
// 		{
// 			int options = placableOptions(lines[i], state.coloredLines, conditions, coloredNodes);
// 			int count = __builtin_popcount(options);

// 			switch (count)
// 			{
// 				case 0:
// 					return false;
// 				case 1:
// 				{
// 					int color = __builtin_ctz(options);
// 					int node1 = __builtin_ctzll(lines[i]);
// 					int node2 = __builtin_ctzll(lines[i] ^ (1ULL << node1));

// 					state.nodeInstances[color][node1]++;
// 					state.nodeInstances[color][node2]++;
// 					state.coloredLines[color].push_back(lines[i]);
// 					coloredNodes[color] |= lines[i];
// 					lines.erase(lines.begin() + i);
// 					changes++;
// 					i--;
// 					break;
// 				}
// 				default:
// 					break;
// 			}
// 		}
// 	}
// 	return true;
// }

// static bool recursiveSearch(GraphState state, const std::vector<int>& conditions)
// {
// 	if (state.lines.empty())
// 	{
// 		finalState = state;
// 		return true;
// 	}

// 	for (int color = 0; color < colors; color++)
// 	{
// 		std::vector<i64>::const_iterator bestLine = findBestLine(state.nodeInstances[color], state.lines);
// 		i64 line = *bestLine;

// 		int node1 = __builtin_ctzll(line);
// 		int node2 = __builtin_ctzll(line ^ (1ULL << node1));
		
// 		if (legalClusterSizes(state.nodeInstances[color], state.coloredLines[color], line, conditions[color]) == true)
// 		{
// 			/*	backup the state to restore it afterwards if the path leads to a dead end	*/

// 			GraphState backupState = state;

// 			state.nodeInstances[color][node1]++;
// 			state.nodeInstances[color][node2]++;
// 			state.lines.erase(bestLine);
// 			state.coloredLines[color].push_back(line);
// 			if (attemptToSolve(state, conditions) == true)
// 			{
// 				if (recursiveSearch(state, conditions) == true)
// 				{
// 					return true;
// 				}
// 			}
// 			state = backupState;
// 		}
// 	}
// 	return false;
// }

void	findSolution(Graph& graph, const std::vector<int>& conditions)
{
	std::signal(SIGINT, [](int signum)
	{
		std::cout << "\nInterrupt signal (" << signum << ") received. Exiting..." << std::endl;
		std::exit(signum);
	});
	Stopwatch stopwatch;
	Stopwatch totalStopwatch;
	
	totalStopwatch.start();
	for (int totalNodes = Graph::startingNodes; totalNodes <= Graph::maximumNodeSize; totalNodes++)
	{
		std::cout << "========================Trying " << totalNodes << " nodes========================" << std::endl;
		stopwatch.start();
		
		/*	If the amount of nodes == 3, coloring 0-1 1-2 and 2-0 would form a cluster of size 3.
		For higher values, the outer ring only forms clusters of size 2.	*/
		
		if (graph.solve() == true)
		{
			std::vector<std::vector<i64>> result = graph.getFullGraph();
			stopwatch.stop();
			if (totalNodes > 3 && checkSolution(result, conditions) == false)
			{
				std::cerr << "Error: solver finished but does not satisfy conditions" << std::endl;
			}
			std::cout << "Solution found! " << stopwatch << std::endl;
			printSolution(result, totalNodes);
		}
		else
		{
			stopwatch.stop();
			totalStopwatch.stop();
			std::cout << "Success! No solution found for " << totalNodes << " nodes.\n" << stopwatch << ".\nTotal: " << totalStopwatch << std::endl;
			return;
		}
		stopwatch.reset();
		graph.increaseNodes();
	}
}
