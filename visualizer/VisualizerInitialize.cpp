#include "Visualizer.hpp"

const char* glsl_version = "#version 150";

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void	Visualizer::initialize()
{
	glfwSetErrorCallback(glfw_error_callback);
	if (glfwInit() == GLFW_FALSE)
	{
		throw std::bad_alloc();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	this->window = glfwCreateWindow(1440, 1440, "Graph", nullptr, nullptr);
	if (this->window == nullptr)
	{
		throw std::bad_alloc();
	}
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(true);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(this->window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}