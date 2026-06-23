#pragma once

#include "ramsey.hpp"

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

	bool	add(int a, int b);
	bool	add(i64 line);

	void	pop();
	void	increase();

	const std::vector<i64>&	getLines() const noexcept { return lines; }

	private:

	std::vector<i64>	lines;
	std::vector<int>	instances;

	std::vector<i64>	linesToCheck;
	std::vector<int>	indexes;

	int	maxSize;
	int nodes;
	int	nodesForCluster;
	
	bool	lineFormsCluster(int a, int b);
	bool	enumerateCombinationsAndCheck(i64 newLine);
};