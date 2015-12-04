#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H
#include "glm\glm.hpp"
#include "GLFW\glfw3.h"
#include "Matikka.h"
void getPolygonBoudningBox(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
	//glfwSwapBuffers(window);
	/*glm::vec2 topleft(x1,y1);
	glm::vec2 topright(aabb[1], aabb[2]);
	glm::vec2 bottomleft(aabb[0], aabb[3]);
	glm::vec2 bottomright(aabb[1], aabb[3]);
	glm::mat2x2 pointMatrix(topleft, topright,
							bottomleft, bottomright);
	drawPolygonBoundingBox(pointMatrix);*/
}

//void getSpriteBoundingBox(unsigned char x)
//{
//
//}
//void drawPolygonBoundingBox(glm::mat2x2 pointMatrix)
//{
//
//	GLfloat x1 = pointMatrix[0]; GLfloat x2; GLfloat y1; GLfloat y2;
//		
//
//}
#endif