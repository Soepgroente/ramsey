#include "ramsey.hpp"

void	printSolution(const std::vector<std::vector<i64>>& colorLines, const std::vector<i64>& lines, int nodes)
{
	std::ofstream		file;
	std::string			filename = "results/Result_with_" + std::to_string(nodes) + "_nodes.txt";
	std::vector<int>	indices(colorLines.size(), 0);
	std::vector<char>	results;

	file.open(filename);
	if (file.is_open() == false)
	{
		std::cerr << "Failed to open file " << filename << std::endl;
		exit(EXIT_FAILURE);
	}
	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < colorLines.size(); j++)
		{
			if (indices[j] < (int)colorLines[j].size() && lines[i] == colorLines[j][indices[j]])
			{
				results.push_back(static_cast<char>(j + '0'));
				indices[j]++;
				break;
			}
		}
	}
	file.write(results.data(), results.size());
	file.close();
}
