#include "GL\glew.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\transform.hpp"
#include "GLFW\glfw3.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "Shader.h"
#include "Texture.h"
#include "Triangle.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\transform.hpp"
#include "glm\glm.hpp"

//namespace
//{
	GLFWwindow* window;
	GLenum err;

	GLuint programID;
	GLuint MVP_MatrixID;
	GLuint vertexbuffer;
	GLuint VertexArrayID;
	GLuint colorbuffer;

	GLuint textureVertexbuffer;
	GLuint textureVertexArrayID;
	GLuint textureProgramID;
	GLuint TextureID;
	GLuint Texture;
	GLuint uvbuffer;
	GLuint indexbuffer;


	float alpha = 0.0f;

	glm::mat4 MVP();
	glm::vec2 wh;
	int N_triangles;
	int error_code;
	void Render();
	int Init(void);
	int num;
	int w;
	int h;
//}


int Init(void)
{
	if (!glfwInit())
	{
		error_code = 101;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	window = glfwCreateWindow(640, 480, "Graphics Engine", NULL, NULL);
	if (window == NULL)
	{
		error_code = 102;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		error_code = 103;
		return -1;
	}
	glClearColor(0.25f, 0.25f, 0.25f, 0.0f);
	
	glEnable(GL_TEXTURE_2D);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	programID = LoadShaders(
		"VertexShader.vertexshader",
		"FragmentShader.fragmentshader",
		"GeometryShader.geometryshader");
		
	MVP_MatrixID = glGetUniformLocation(programID, "MVP");
	
	// Vertex
	static const GLfloat g_vertex_buffer_data[] =
	{
		-0.5f, -0.5f,  0.0f, 
		 0.5f,  0.0f,  0.0f, 
		 0.0f,  0.5f,  0.0f,
	};
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Color
	static const GLfloat g_color_buffer_data[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};
	N_triangles = 1;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	// Index
	static const GLubyte g_indices[] =
	{
		0, 1, 2,
	};
	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), g_indices, GL_STATIC_DRAW);

	// UV
	static const GLfloat g_uv_buffer_data[] =
	{
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
	};
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	// loading texture
	TextureID = glGetUniformLocation(programID, "myTextureSampler");
	Texture = loadBMP_custom(w,h,"./uvtemplate.bmp");
	
	return 0;

}
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	Triforce(num);
	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(0.0f, 0.5f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(-0.5f, -0.5f, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(0.5f, -0.5f, 0.0f);
	//glEnd(); 
	glfwSwapBuffers(window);
}
void Uninit(void)
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
}

