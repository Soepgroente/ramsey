#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_opengl3_loader.h"
#include <stdio.h>
#include <iostream>
#include "imgui_internal.h"
#include </opt/homebrew/include/GLFW/glfw3.h> // Will drag system OpenGL headers
// #include <GLFW/glfw3.h>

#include "ramsey.hpp"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

enum Colors
{
	blue,
	red,
	green,
	yellow,
	orange,
	purple,
	cyan,
	pink,
	black
};

class Visualizer
{
	public:

	Visualizer();
	Visualizer(const Visualizer& other) = delete;
	Visualizer& operator=(const Visualizer& other) = delete;
	~Visualizer();

	void	run();

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	private:

	std::vector<std::vector<int>>	lineColors;
    static Visualizer* 				instance;
	int								totalNodes;
	int								nodeAmount;
    std::vector<ImVec2>				nodePositions;

	GLFWwindow*	window;

	void	keyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mods);
    void	mouseButtonCallbackImpl(GLFWwindow* window, int button, int action, int mods);
	void	initialize();
	void	render();
	void	renderGraph(ImDrawList* draw_list, const ImVec2& windowPos, const std::vector<int>& lines);
};
