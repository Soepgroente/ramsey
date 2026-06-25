#include "MonoGraph.hpp"

#include <iostream>

MonoGraph::MonoGraph(int condition, int nodes)
{
	maxSize = condition;
	this->nodes = nodes;
	nodesForCluster = nodesInACluster[condition];
	instances.assign(nodes, 0);
	indexes.assign(nodesForCluster - 1, 0);
}

bool	MonoGraph::enumerateCombinationsAndCheck(i64 newLine)
{
	const int	arraySize = static_cast<int>(linesToCheck.size());
	const int	bufferSize = nodesForCluster - 1;

	for (int i = 0; i < bufferSize; i++)
	{
		indexes[i] = i;
	}
	/*	Check all combinations of lines that connect to at least maxSize nodes.
		By using bitwise AND we can efficiently check if all lines are part of the same group of maxSize nodes	*/
	
	while (true)
	{
		i64	cluster = newLine;
		for (int i = 0; i < bufferSize; i++)
		{
			cluster |= linesToCheck[indexes[i]];
		}
		if (__builtin_popcountll(cluster) == maxSize)
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
	}
	return true;
}

#include "ramsey.hpp"

bool	MonoGraph::lineFormsCluster(int a, int b)
{
	const int size = maxSize - 1;

	/*	If the amount of connections is less than maxSize - 1,
	it's impossible to form a cluster with the new line	*/

	if (instances[a] < size || instances[b] < size)
	{
		return false;
	}

	linesToCheck.clear();

	instances[a]++;
	instances[b]++;
	
	/*	Fill vector with lines that could potentially form a cluster,
		if a node is connected less than maxSize times, it can't be part of a cluster of maxSize	*/
	
	for (size_t i = 0; i < lines.size(); i++)
	{
		int ca = __builtin_ctzll(lines[i]);
		int cb = __builtin_ctzll(lines[i] ^ (1ULL << ca));
		if (instances[ca] >= maxSize && instances[cb] >= maxSize)
		{
			linesToCheck.push_back(lines[i]);
		}
	}
	instances[a]--;
	instances[b]--;

	/*	If we find fewer lines than a full cluster needs, early exit	*/

	if (static_cast<int>(linesToCheck.size()) < nodesForCluster)
	{
		return false;
	}
	return enumerateCombinationsAndCheck(i64(1 << a | 1 << b));
}

std::vector<i64>	MonoGraph::findUnplacableLines(const std::vector<i64>& unplacedLines)
{
	std::vector<i64>	clusterFormingLines{};
	std::vector<int>	hotNodes;

	/*	get nodes that could be part of a cluster	*/

	for (size_t i = 0; i < indexes.size(); i++)
	{
		if (indexes[i] >= maxSize)
		{
			hotNodes.push_back(i);
		}
	}

	/*	add all lines that form a cluster	*/
	if (static_cast<int>(hotNodes.size()) >= maxSize)
	{
		for (size_t i = 0; i < hotNodes.size() - 1; i++)
		{
			for (size_t j = i + 1; j < hotNodes.size(); j++)
			{
				i64	line = 1 << i | 1 << j;
				if (std::find(unplacedLines.begin(), unplacedLines.end(), line) != unplacedLines.end() &&
						lineFormsCluster(i, j) == true)
				{
					clusterFormingLines.push_back(line);
				}
			}
		}
	}
	return clusterFormingLines;
}

bool	MonoGraph::isAddable(i64 line)
{
	int a = __builtin_ctzll(line);
	int b = __builtin_ctzll(line ^ (1ULL << a));

	if (lineFormsCluster(a, b) == true)
	{
		return false;
	}
	return true;
}

bool	MonoGraph::add(i64 line)
{
	int a = __builtin_ctzll(line);
	int b = __builtin_ctzll(line ^ (1ULL << a));

	if (lineFormsCluster(a, b) == true)
	{
		return false;
	}
	instances[a]++;
	instances[b]++;
	lines.push_back(line);
	return true;
}

void	MonoGraph::pop()
{
	int a = __builtin_ctzll(lines.back());
	int b = __builtin_ctzll(lines.back() ^ (1ULL << a));

	instances[a]--;
	instances[b]--;
	lines.pop_back();
}

void	MonoGraph::increase()
{
	nodes++;
	instances.assign(nodes, 0);
	lines.clear();
	linesToCheck.clear();
}
