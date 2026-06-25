#include "ramsey.hpp"

#include "MonoGraph.hpp"

bool	checkSolution(std::vector<MonoGraph>& colors)
{
	for (size_t i = 0; i < colors.size(); i++)
	{
		if (colors[i].checkEntireConfiguration() == false)
		{
			return false;
		}
	}
	return true;
}
