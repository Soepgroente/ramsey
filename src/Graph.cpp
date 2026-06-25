#include "Graph.hpp"

#include <algorithm>
#include <iostream>

Graph::Graph(const std::vector<int>& conditions)
{
	amountOfColors = static_cast<int>(conditions.size());

	for (int i = 0; i < amountOfColors; i++)
	{
		colors.push_back(MonoGraph(conditions[i], Graph::startingNodes));
		fullGraph.push_back(std::vector<i64>{});
	}
	nodes = Graph::startingNodes;
	createLines();
	remainingLines = lines;
}

void	Graph::increaseNodes()
{
	nodes++;
	for (MonoGraph& color : colors)
	{
		color.increase();
	}
	createLines();

	/*	Color outer ring with first color	*/

	if (nodes > 3)
	{
		for (size_t i = 0; i < lines.size(); i++)
		{
			int a = __builtin_ctzll(lines[i]);
			int b = __builtin_ctzll(lines[i] ^ (1ULL << a));

			if (std::abs(a - b) == 1 || (a == 0 && std::abs(a - b) == nodes - 1))
			{
				colors[0].forceAdd(lines[i]);
				lines.erase(lines.begin() + i);
				i--;
			}
		}
	}
	remainingLines = lines;
}

void	Graph::createLines()
{
	lines.clear();
	lines.reserve(nodes * (nodes - 1) / 2);
	for (i32 i = 0; i < nodes - 1; i++)
	{
		for (i32 j = i + 1; j < nodes; j++)
		{
			lines.push_back(1ULL << i | 1ULL << j);
		}
	}
	std::sort(lines.begin(), lines.end());
}

void	Graph::reversePlacements(std::vector<int>& placements)
{
	std::reverse(placements.begin(), placements.end());
	for (int x : placements)
	{
		lines.push_back(colors[x].back());
		colors[x].pop();
	}
	std::sort(lines.begin(), lines.end());
}

bool	Graph::placeLogically(int i, std::vector<int>& placements)
{
	std::vector<i64> unplacableLines = colors[i].findUnplacableLines(lines);
	int c = 0;

	for (size_t j = 0; j < unplacableLines.size(); j++)
	{
		i64 line = unplacableLines[j];

		for (int clr = 1; clr <= amountOfColors; clr++)
		{
			if (clr == i)
			{
				continue;
			}
			if (colors[clr - 1].isAddable(line) == true)
			{
				if (c == 0)
				{
					c = clr - 1;
				}
				else
				{
					c = -1;
					break;
				}
			}
		}
		if (c == 0)
		{
			reversePlacements(placements);
			return false;
		}
		if (c > 0)
		{
			colors[c].forceAdd(line);
			placements.push_back(c);
		}
	}
	return true;
}

bool	Graph::solve()
{
	if (remainingLines.empty() == false)
	{
		i64 line = remainingLines.front();

		for (int i = 0; i < amountOfColors; i++)
		{
			if (colors[i].add(line) == true)
			{
				remainingLines.erase(remainingLines.begin());
				std::vector<int> placedNumbers;
				
				if (placeLogically(i, placedNumbers) == true && solve() == true)
				{
					return true;
				}
				reversePlacements(placedNumbers);
				remainingLines.insert(remainingLines.begin(), line);
				colors[i].pop();
			}
		}
		return false;
	}
	return true;
}

std::vector<std::vector<i64>>&	Graph::getFullGraph()
{
	for (int i = 0; i < amountOfColors; i++)
	{
		fullGraph[i] = colors[i].getLines();
	}
	return fullGraph;
}