#include "ramsey.hpp"

/*	order: 0-1, 0-n, 1-2, 1-n, etc	*/

void	printSolution(std::vector<std::vector<i64>>& colorLines, int nodes)
{
	std::ofstream		file;
	std::string			filename = "results/Result_with_" + std::to_string(nodes) + "_nodes.txt";
	std::string			results;

	file.open(filename);
	if (file.is_open() == false)
	{
		std::cerr << "Failed to open file " << filename << std::endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < nodes - 1; i++)
	{
		for (int j = i + 1; j < nodes; j++)
		{
			i64 line = (1ULL << i) | (1ULL << j);
			bool found = false;
			for (size_t k = 0; k < colorLines.size(); k++)
			{
				std::vector<i64>& color = colorLines[k];
				std::vector<i64>::iterator location = std::find(color.begin(), color.end(), line);

				if (location != color.end())
				{
					results += std::to_string(k);
					color.erase(location);
					found = true;
					break;
				}
			}
			if (found == false)
			{
				std::cerr << "Line " << i << " - " << j << " not found in any color" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
	}
	file.write(results.data(), results.size());
	file.close();
}
