#include "Visualizer.hpp"
#include <stdlib.h>
#include <unistd.h>

Visualizer* Visualizer::instance = nullptr;

Visualizer::Visualizer()
{
	const std::string	filename = "results/Result_with_";
	std::ifstream		file;
	std::string			extension = "2_nodes.txt";
	std::string			line(1000, '\0');
	int i = 2;

	instance = this;
	this->lineColors.push_back(std::vector<int>());
	this->lineColors.push_back(std::vector<int>());
	while (access((filename + extension).c_str(), F_OK) == 0)
	{
		file.open(filename + extension);
		if (file.is_open() == false)
		{
			std::cerr << "Failed to open file " << filename + extension << std::endl;
			exit(EXIT_FAILURE);
		}
		std::vector<int> colors;

		file.seekg(0, std::ios::end);
		std::streamsize fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		std::string line(fileSize, '\0');
		file.read(&line[0], fileSize);
		size_t bytesRead = static_cast<size_t>(file.gcount());

		for (size_t j = 0; j < bytesRead; j++)
		{
			if (std::isdigit(line[j]) != 0)
			{
				colors.push_back(static_cast<int>(line[j] - '0'));
			}
		}
		this->lineColors.push_back(colors);
		file.close();
		i++;
		extension = std::to_string(i) + "_nodes.txt";
	}
	if (i == 2)
	{
		std::cerr << "No results found" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	this->totalNodes = i;
	this->nodeAmount = 2;
}

Visualizer::~Visualizer()
{
	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void	Visualizer::run()
{
	initialize();
	render();
}
