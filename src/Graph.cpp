#include "Graph.hpp"

Graph::Graph(const std::vector<int>& conditions)
{
	amountOfColors = static_cast<int>(conditions.size());

	colors.reserve(amountOfColors);
	fullGraph.reserve(amountOfColors);
	for (int i = 0; i < amountOfColors; i++)
	{
		colors.push_back(MonoGraph(conditions[i], Graph::startingNodes));
		fullGraph.push_back(std::vector<i64>());
	}
}

void	Graph::increaseNodes()
{
	nodes++;
	lines.clear();
	for (MonoGraph& color : colors)
	{
		color.increase();
	}
	createLines();

	/*	Color outer ring with first color	*/

	for (size_t i = 0; i < lines.size();)
	{
		int node1 = __builtin_ctzll(lines[i]);
		int node2 = __builtin_ctzll(lines[i] ^ (1ULL << node1));

		if (std::abs(node1 - node2) == 1 || (node1 == 0 && std::abs(node1 - node2) == nodes -1))
		{
			colors[0].add(lines[i]);
			lines.erase(lines.begin() + i);
		}
		else
		{
			i++;
		}
	}
}

void	Graph::createLines()
{
	lines.reserve(nodes * (nodes - 1) / 2);
	for (i32 i = 0; i < nodes - 1; i++)
	{
		for (i32 j = i + 1; j < nodes; j++)
		{
			lines.push_back(1ULL << i | 1ULL << j);
		}
	}
	std::sort(lines.begin(), lines.end());
	std::reverse(lines.begin(), lines.end());
}

bool	Graph::solve()
{
	if (lines.empty() == true)
	{
		return true;
	}
}

const std::vector<std::vector<i64>>&	Graph::getFullGraph()
{
	for (int i = 0; i < amountOfColors; i++)
	{
		fullGraph[i] = colors[i].getLines();
	}
	return fullGraph;
}