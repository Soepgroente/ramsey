#include "ramsey.hpp"

/*	printing order: 0-1, 0-2, 0-3... 0-n, 1-2, 1-3... 1-n... (n-1)-n	*/

void	printSolution(std::vector<std::vector<i64>>& coloredLines, int nodes)
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
			for (size_t k = 0; k < coloredLines.size(); k++)
			{
				std::vector<i64>& color = coloredLines[k];
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
				std::cerr << "Line " << i << "-" << j << " (" << line << ") not found in any color" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
	}
	file.write(results.data(), results.size());
	file.close();
}

void	printLine(i64 line)
{
	int node1 = __builtin_ctzll(line);
	int node2 = __builtin_ctzll(line ^ (1ULL << node1));
	std::cout << node1 << " - " << node2 << std::endl;
}

