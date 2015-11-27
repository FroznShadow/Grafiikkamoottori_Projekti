#include "GLFW\glfw3.h"
#include <math.h>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\transform.hpp"
#include <stdio.h>
#include <stdlib.h>

GLFWwindow* window;
float alpha = 1.0f;
glm::mat4 MVP(1.0);

void RotateMath()
{
	glm::vec3 x_axis(1.0, 0.0, 0.0);
	glm::vec3 y_axis(0.0, 1.0, 0.0);
	glm::vec3 z_axis(0.0, 0.0, 1.0);
	glm::vec3 cam_pos(0, 0, 0);
	glm::vec3 cam_up = y_axis;
	glm::vec3 cam_right = x_axis;
	glm::vec3 cam_front = -z_axis;
	glm::mat4 P = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glm::mat4 V = glm::ortho(-1.0f, 1.0f, -1.0f*height / width, 1.0f*height / width);
	glm::mat4 VP = V*P;
	glm::mat4 M = glm::rotate(alpha, z_axis)*glm::translate(glm::vec3(0.0, 0.5, 0))*glm::scale(glm::vec3(0.25));
	MVP = VP*M;
}