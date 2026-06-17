#include "Visualizer.hpp"

void	Visualizer::keyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
    {
        glfwSetWindowShouldClose(window, true);
    }
	if (key == GLFW_KEY_KP_ADD && action == GLFW_RELEASE)
	{
		if (nodeAmount < totalNodes - 1)
		{
			nodeAmount++;
		}
	}
	if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_RELEASE)
	{
		if (nodeAmount > 0)
		{
			nodeAmount--;
		}
	}
}

void	Visualizer::mouseButtonCallbackImpl(GLFWwindow* window, int button, int action, int mods)
{
	(void)mods;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		double	x;
		double	y;

		glfwGetCursorPos(window, &x, &y);
	}
}

void	Visualizer::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	instance->keyCallbackImpl(window, key, scancode, action, mods);
}

void	Visualizer::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	instance->mouseButtonCallbackImpl(window, button, action, mods);
}