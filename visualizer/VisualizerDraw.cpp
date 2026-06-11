#include "Visualizer.hpp"

void	Visualizer::render()
{
	int display_w, display_h;

	while (glfwWindowShouldClose(window) == GLFW_FALSE)
	{
		glfwPollEvents();
		
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);

		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);

		ImGui::Begin("Main window", nullptr);

		renderGraph(ImGui::GetWindowDrawList(), ImGui::GetWindowPos(), lineColors[nodeAmount]);
		ImGui::PopStyleColor();
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}
}

static std::vector<ImVec2> calculateNodePositions(int numNodes, const ImVec2& center, ImVec2 win)
{
	const float PI = 3.14159265359f;
	std::vector<ImVec2> positions;
	float angle = 0.0f;

	win.x *= 0.44f;
	win.y *= 0.44f;

	for (int i = 0; i < numNodes; i++)
	{
		angle = (i * 2 * PI) / numNodes + 1.5f * PI;
		positions.push_back(ImVec2(center.x + win.x * cos(angle), center.y + win.y * sin(angle)));
	}
	return positions;
}

void	Visualizer::renderGraph(ImDrawList* draw_list, const ImVec2& windowPos, const std::vector<int>& linesToDraw)
{
	if (draw_list == nullptr)
	{
		std::cerr << "Draw list is null" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	ImGui::Text("Showing configuration for %d nodes", nodeAmount);

	constexpr std::array<ImU32, 9> colorsToRGBA =
	{
		IM_COL32(0, 0, 255, 255),		// blue
		IM_COL32(255, 0, 0, 255),		// red
		IM_COL32(0, 255, 0, 255),		// green
		IM_COL32(255, 255, 0, 255),		// yellow
		IM_COL32(255, 165, 0, 255),		// orange
		IM_COL32(128, 0, 128, 255),		// purple
		IM_COL32(0, 255, 255, 255),		// cyan
		IM_COL32(255, 105, 180, 255),	// pink
		IM_COL32(0, 0, 0, 255),			// black
	};

	ImVec2 dimensions = ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

	const float baseThickness = (dimensions.x + dimensions.y) * 0.005f;

	float scaleFactor = 1.0f - (std::min(static_cast<float>(nodeAmount), 25.0f) / 25.0f);
	float lineThickness = std::max(baseThickness * scaleFactor, 1.0f);

	float nodeRadius = std::max(lineThickness * 5.0f, baseThickness);
	float circlePadding = std::max(nodeRadius * 0.2f, 1.0f);
	int pos = 0;
	nodePositions = calculateNodePositions(nodeAmount, {windowPos.x + dimensions.x * 0.5f, windowPos.y + dimensions.y * 0.5f}, dimensions);

	for (int x = 0; x < nodeAmount; x++)
	{
		for (int y = x + 1; y < nodeAmount; y++)
		{
			draw_list->AddLine(nodePositions[x], nodePositions[y], colorsToRGBA[linesToDraw[pos]], lineThickness);
			pos++;
		}
	}

	for (size_t i = 0; i < nodePositions.size(); i++)
	{
		ImVec2 pos(nodePositions[i].x, nodePositions[i].y);

		std::string tmp = std::to_string(i);
		const char* nodeText = tmp.c_str();
		draw_list->AddCircleFilled(pos, nodeRadius, colorsToRGBA[yellow], 0);
		draw_list->AddCircle(pos, nodeRadius, colorsToRGBA[black], 0, circlePadding);
		draw_list->AddText(
			ImGui::GetFont(),
			nodeRadius,
			ImVec2(nodePositions[i].x - static_cast<float>(tmp.size()) * 0.25f * nodeRadius, nodePositions[i].y - nodeRadius * 0.5f),
			IM_COL32(0, 0, 0, 255),
			nodeText
		);
	}
}
