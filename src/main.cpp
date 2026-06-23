#include "ramsey.hpp"

static std::vector<int>	getInput(char** argv)
{
	std::vector<int>	colors;

	for (int i = 1; argv[i] != nullptr; i++)
	{
		colors.push_back(std::stoi(argv[i]));
		if (colors.back() < 3 || colors.back() > 10)
		{
			throw std::invalid_argument("Arguments must be between 3-10.");
		}
	}
	if (colors.size() < 2 || colors.size() > 10)
	{
		throw std::invalid_argument("Error: Number of colors must be between 2 and 10.");
	}
	return colors;
}


static void	printUserInput(const std::vector<int>& conditions)
{
	for (size_t i = 0; i < conditions.size(); i++)
	{
		std::cout << colorPrints[i] << conditions[i] << " ";
	}
	std::cout << RESET << std::endl;
}

int main(int argc, char** argv)
{
	std::vector<int>	conditions = getInput(argv);

	std::sort(conditions.begin(), conditions.end());
	printUserInput(conditions);
	if (argc < 2)
	{
		std::cerr << "Usage: \"" << argv[0] << " [color 1 max], [color 2 max] ... [color N max]\"" << std::endl;
		return 1;
	}
	if (argc > 10)
	{
		std::cerr << "That's too many colors, this poor program cannot handle such beauty" << std::endl;
		return 2;
	}
	system("rm -f results/*");

	Graph graph(conditions);

	findSolution(graph);

	char *const args[] = {(char*)"visuals.out", NULL};

	execv("visuals.out", args);
}
