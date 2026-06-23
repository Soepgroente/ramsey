#pragma once

#include <vector>
#include "MonoGraph.hpp"

using i64 = int64_t;

struct Graph
{
	public:
	
	Graph() = delete;
	Graph(const std::vector<int>& conditions);
	~Graph() = default;
	Graph(const Graph& other) = default;
	Graph(Graph&& other) noexcept = default;
	Graph& operator=(const Graph& other) = default;
	Graph& operator=(Graph&& other) noexcept = default;
	
	bool	solve();
	void	increaseNodes();

	const std::vector<std::vector<i64>>&	getFullGraph();

	static const int startingNodes = 2;
	static const int maximumNodeSize = 64;

	private:
	
	std::vector<i64> lines;
	std::vector<i64> remainingLines;
	std::vector<MonoGraph> colors;
	std::vector<std::vector<i64>> fullGraph;

	int nodes;
	int amountOfColors;

	void	createLines();
};