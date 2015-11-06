#include "Renderer.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		num += 1;
		if (num > 3)
			num = 0;
	}
	if (key == GLFW_KEY_W)
	{
		cameraY += 0.01f;
	}
	if (key == GLFW_KEY_S)
	{
		cameraY -= 0.01f;
	}
	if (key == GLFW_KEY_A)
	{
		cameraX -= 0.01f;
	}
	if (key == GLFW_KEY_D)
	{
		cameraX += .01f;
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();
	glTranslatef(-cameraX, -cameraY, 0.0f);
	glPushMatrix();
}
int main(int argc, char* argv[])
{
	if (Init() != 0)
		return error_code;
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	glfwSetKeyCallback(window, key_callback);
	
	while (!glfwWindowShouldClose(window))
	{
		Render();
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}