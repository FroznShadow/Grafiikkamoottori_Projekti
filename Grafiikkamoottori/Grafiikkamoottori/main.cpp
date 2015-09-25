#include "Renderer.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char* argv[])
{
	if (Init() != 0)
		return error_code;

	glfwSetKeyCallback(window, key_callback);
	while (!glfwWindowShouldClose(window))
	{
		Render();
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}