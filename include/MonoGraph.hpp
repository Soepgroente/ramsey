#pragma once

#include <vector>
#include "types.hpp"

class MonoGraph
{
	public:
		
	MonoGraph() = delete;
	~MonoGraph() = default;
	MonoGraph(int condition, int nodes);
	MonoGraph(const MonoGraph& other) = default;
	MonoGraph(MonoGraph&& other) noexcept = default;
	MonoGraph& operator=(const MonoGraph& other) = default;
	MonoGraph& operator=(MonoGraph&& other) noexcept = default;

	bool	isAddable(i64 line);
	bool	add(i64 line);
	void	forceAdd(i64 line);
	bool	preAdd(i64 line);

	i64		back();
	void	pop();
	void	remove(i64 line);
	void	increase();

	bool	checkEntireConfiguration();

	std::vector<i64> findUnplacableLines(const std::vector<i64>& unplacedLines);
	const std::vector<i64>&	getLines() const noexcept { return lines; }

	private:

	std::vector<i64>	lines;
	std::vector<int>	instances;

	std::vector<i64>	linesToCheck;
	std::vector<int>	indexes;

	int	clusterSize;
	int nodes;
	int	nodesForCluster;
	
	bool	lineIsPlacable(int a, int b);
	bool	enumerateCombinationsAndCheck(i64 newLine);
};