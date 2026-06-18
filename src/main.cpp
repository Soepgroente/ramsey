#include "ramsey.hpp"

std::vector<int>	getInput(char** argv);

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

	std::cout << "Input: " << std::flush;
	printUserInput(conditions);
	std::sort(conditions.begin(), conditions.end());
	std::cout << "Sorted input: ";
	printUserInput(conditions);
	if (argc < 2)
	{
		std::cerr << "Usage: \"" << argv[0] << " [color 1 max], [color 2 max] ... [color N max]\"" << std::endl;
		return (1);
	}
	if (argc > 10)
	{
		std::cerr << "That's too many colors, this poor program cannot handle such beauty" << std::endl;
		return (2);
	}
	system("rm -f results/*");
	findSolution(conditions);

	char *const args[] = {(char*)"visuals.out", NULL};

	execv("visuals.out", args);
}
