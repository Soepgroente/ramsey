#include "ramsey.hpp"

std::vector<int>	getInput(char** argv);

int main(int argc, char** argv)
{
	std::vector<int>	conditions = getInput(argv);

	if (argc < 2)
	{
		std::cerr << "Usage: \"" << argv[0] << " [color 1 max], [color 2 max] ... [color N max]\"" << std::endl;
		return (1);
	}
	if (argc > 7)
	{
		std::cerr << "That's too many colors, this poor program cannot handle such beauty" << std::endl;
		return (2);
	}
	system("rm -f results/*");
	findSolution(conditions);

	char *const args[] = {(char*)"visuals.out", NULL};

	execv("visuals.out", args);
}
