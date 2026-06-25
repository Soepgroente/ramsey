#include "ramsey.hpp"

/* bool	checkSolution(const std::vector<std::vector<i64>>& coloredLines, const std::vector<int>& conditions)
{
	for (size_t i = 0; i < coloredLines.size(); i++)
	{
		if (static_cast<int>(coloredLines[i].size()) < nodesInACluster[conditions[i]])
		{
			continue;
		}
		std::vector<i64> lines = coloredLines[i];
		for (size_t j = 0; j < coloredLines[i].size(); j++)
		{
			i64 testLine = lines[j];
			lines.erase(lines.begin() + j);
			if (legalClusterSizes2(lines, testLine, conditions[i]) == false)
			{
				printLine(testLine);
				std::cerr << "Cluster of size " << conditions[i] << " found in" << colorPrints[i] << " color " << RESET << std::endl;
				return false;
			}
			lines.insert(lines.begin() + j, testLine);
		}
	}
	return true;
} */
