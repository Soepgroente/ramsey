#include "MonoGraph.hpp"

#include <cassert>
#include <iostream>

MonoGraph::MonoGraph(int condition, int nodes)
{
	clusterSize = condition;
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
	/*	Check all combinations of lines that connect to at least clusterSize nodes.
		By using bitwise AND we can efficiently check if all lines are part of the same group of clusterSize nodes	*/
	
	while (true)
	{
		i64	cluster = newLine;
		for (int i = 0; i < bufferSize; i++)
		{
			cluster |= linesToCheck[indexes[i]];
		}
		if (__builtin_popcountll(cluster) == clusterSize)
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

bool	MonoGraph::lineIsPlacable(int a, int b)
{
	const int size = clusterSize - 1;

	/*	If the amount of connections is less than clusterSize - 1,
	it's impossible to form a cluster with the new line	*/

	if (instances[a] < size - 1 || instances[b] < size - 1)
	{
		return true;
	}

	linesToCheck.clear();

	instances[a]++;
	instances[b]++;
	
	/*	Fill vector with lines that could potentially form a cluster,
		if a node is connected less than clusterSize times, it can't be part of a cluster of clusterSize	*/

	for (size_t i = 0; i < lines.size(); i++)
	{
		int ca = __builtin_ctzll(lines[i]);
		int cb = __builtin_ctzll(lines[i] ^ (1ULL << ca));
		if (instances[ca] >= size && instances[cb] >= size)
		{
			linesToCheck.push_back(lines[i]);
		}
	}
	instances[a]--;
	instances[b]--;

	/*	If we find fewer lines than a full cluster needs, early exit	*/

	if (static_cast<int>(linesToCheck.size()) + 1 < nodesForCluster)
	{
		return true;
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
		if (indexes[i] >= clusterSize)
		{
			hotNodes.push_back(i);
		}
	}

	/*	add all lines that form a cluster	*/
	if (static_cast<int>(hotNodes.size()) >= clusterSize)
	{
		for (size_t i = 0; i < hotNodes.size() - 1; i++)
		{
			for (size_t j = i + 1; j < hotNodes.size(); j++)
			{
				i64	line = 1 << i | 1 << j;
				if (std::find(unplacedLines.begin(), unplacedLines.end(), line) != unplacedLines.end() &&
						lineIsPlacable(i, j) == true)
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

	return lineIsPlacable(a, b);
}

bool	MonoGraph::preAdd(i64 line)
{
	const int size = clusterSize - 2;

	int a = __builtin_ctzll(line);
	int b = __builtin_ctzll(line ^ (1ULL << a));

	if (instances[a] == size && instances[b] == size)
	{
		return false;
	}
	if (instances[a] <= size && instances[b] <= size)
	{
		instances[a]++;
		instances[b]++;
		lines.push_back(line);
		return true;
	}
	return false;
}

bool	MonoGraph::add(i64 line)
{
	int a = __builtin_ctzll(line);
	int b = __builtin_ctzll(line ^ (1ULL << a));

	if (lineIsPlacable(a, b) == true)
	{
		instances[a]++;
		instances[b]++;
		lines.push_back(line);
		return true;
	}
	return false;
}

void	MonoGraph::forceAdd(i64 line)
{
	int a = __builtin_ctzll(line);
	int b = __builtin_ctzll(line ^ (1ULL << a));

	instances[a]++;
	instances[b]++;
	lines.push_back(line);
}

void	MonoGraph::pop()
{
	int a = __builtin_ctzll(lines.back());
	int b = __builtin_ctzll(lines.back() ^ (1ULL << a));

	instances[a]--;
	instances[b]--;
	lines.pop_back();
}

i64	MonoGraph::back()
{
	return lines.back();
}

void	MonoGraph::increase()
{
	nodes++;
	instances.assign(nodes, 0);
	lines.clear();
	linesToCheck.clear();
}

void	MonoGraph::remove(i64 line)
{
	int a = __builtin_ctzll(lines.back());
	int b = __builtin_ctzll(lines.back() ^ (1ULL << a));

	instances[a]--;
	instances[b]--;
	lines.erase(std::find(lines.begin(), lines.end(), line));
}

bool	MonoGraph::checkEntireConfiguration()
{
	size_t size = lines.size();

	for (size_t i = 0; i < size; i++)
	{
		i64 testLine = lines[i];
		lines.erase(lines.begin() + i);
		if (isAddable(testLine) == false)
		{
			std::cerr << "Cluster found... ";
			printLine(testLine, std::cerr);
			std::cerr << std::endl;
			return false;
		}
		lines.insert(lines.begin() + i, testLine);
	}
	return true;
}