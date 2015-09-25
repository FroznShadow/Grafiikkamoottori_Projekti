#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <stdio.h>
#include <stdlib.h>

namespace
{
	GLFWwindow* window;

}

int Init(void)
{
	if (!glfwInit())
	{
		fprintf(stderr, "nope.avi");
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	window = glfwCreateWindow(640, 480, "Graphics Engine", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		return -1;
	}
	glClearColor(0.25f, 0.25f, 0.25f, 0.0f);
	return 0;

}
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);
}

