#pragma once

#include <vector>

using i64 = int64_t;

struct GraphState
{
	public:

		std::vector<i64> lines;
		std::vector<std::vector<i64>> coloredLines;
		std::vector<std::vector<int>> nodeInstances;

		GraphState() = default;
		~GraphState() = default;
		GraphState(const std::vector<std::vector<i64>>& otherColors, const std::vector<i64>& otherLines)
			: lines(otherLines), coloredLines(otherColors) {}
		GraphState(const GraphState& other) = default;
		GraphState(GraphState&& other) noexcept = default;
		GraphState& operator=(const GraphState& other) = default;
		GraphState& operator=(GraphState&& other) noexcept = default;

		void	clear()	{ lines.clear(); coloredLines.clear(); }
};