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
#include "vertexshader.h"
//namespace
//{
	GLFWwindow* window;
	GLenum err;

	GLuint programID;
	GLuint MVP_MatrixID;
	GLuint wh_VectorID;
	GLuint vertexbuffer;
	GLuint VertexArrayID;
	GLuint colorbuffer;

	GLuint textureVertexbuffer;
	GLuint textureVertexArrayID;
	GLuint textureIndexbuffer;
	GLuint textureProgramID;
	GLuint TextureID;
	GLuint Texture;
	GLuint uvbuffer;
	GLuint indexbuffer;


	float alpha = 0.0f;

	GLfloat cameraX = 0.0f, cameraY = 0.0f;
	glm::mat4 MVP(1.0);
	glm::vec2 wh;
	int N_triangles;
	int N_vertex;
	int error_code;
	void Render();
	int Init(void);
	int InitCamera(void);
	int initBackground(void);
	int num;
	int w;
	int h;
//}

	int InitCamera(void)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glPushMatrix();
		return 0;
	}
	int InitBackground(void)
	{
		glGenVertexArrays(1, &textureVertexArrayID);
		glBindVertexArray(textureVertexArrayID);

		textureProgramID = LoadShaders("Texture.VertexShader", "Texture.FragmentShader","Texture.GeometryShader");
		static const GLfloat texture_vertex_buffer_data[] =
		{
			-1.0, -1.0, 0.9,
			1.0, -1.0, 0.9,
			-1.0, 1.0, 0.9,
			1.0, 1.0, 0.9
		};
		glGenBuffers(1, &textureVertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, textureVertexbuffer);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(texture_vertex_buffer_data), texture_vertex_buffer_data, GL_STATIC_DRAW);
		static const GLubyte texture_indices[] =
		{
			0, 1, 2, 1, 3, 2,
		};
		glGenBuffers(1, &textureIndexbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureIndexbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(texture_indices), texture_indices, GL_STATIC_DRAW);
		static const GLfloat g_uv_buffer_data[] =
		{
			0.0, 0.0,
			1.0, 0.0,
			1.0, 1.0,
			0.0, 1.0,
		};
		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
		TextureID = glGetUniformLocation(textureProgramID, "myTextureSampler");
		Texture = loadBMP_custom(Width,Height,"./uvtemplate.bmp");
		return 0;
	}
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
	InitCamera();
	glClearColor(0.25f, 0.25f, 0.25f, 0.0f);
	
	glEnable(GL_TEXTURE_2D);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	programID = LoadShaders(
		"VertexShader.vertexshader",
		"FragmentShader.fragmentshader",
		"GeometryShader.geometryshader");
		
	MVP_MatrixID = glGetUniformLocation(programID, "MVP");
	wh_VectorID = glGetUniformLocation(programID, "wh");
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
	N_vertex = sizeof(g_indices) / sizeof(*g_indices);
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
	//TextureID = glGetUniformLocation(programID, "myTextureSampler");
	//Texture = loadBMP_custom(w,h,"./uvtemplate.bmp");
	
	//glDrawElements(
	//	GL_TRIANGLES,
	//	sizeof(g_indices),
	//	GL_UNSIGNED_INT,
	//	(void*)0
	//	);

	return 0;

}

void DrawBackground()
{
	glDisable(GL_BLEND);
	glUseProgram(textureProgramID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glUniform1i(TextureID, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, textureVertexbuffer);
	glVertexAttribPointer(
		VERTEX_POSITION,
		3, GL_FLOAT, GL_FALSE,
		0,
		(void*)0
		);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		TEXTURE_DATA,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureIndexbuffer);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
void DrawBox()
{
	glEnable(GL_BLEND);
	glm::vec3 x_axis(1.0, 0.0, 0.0);
	glm::vec3 y_axis(0.0, 1.0, 0.0);
	glm::vec3 z_axis(0.0, 0.0, 1.0);
	glm::vec3 cam_pos(0, 0, 0);
	glm::vec3 cam_up = y_axis;
	glm::vec3 cam_right = x_axis;
	glm::vec3 cam_front = -z_axis;
	glm::mat4 P = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);

	glUseProgram(programID);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glm::mat4 V = glm::ortho(-1.0f, 1.0f, -1.0f*height / width, 1.0f*height / width);
	glm::mat4 VP = V*P;
	glm::mat4 M = glm::rotate(alpha, z_axis)*glm::translate(glm::vec3(0.0, 0.5, 0))*glm::scale(glm::vec3(1.5));
	MVP = VP*M;
	glUniformMatrix4fv(MVP_MatrixID, 1,GL_FALSE, &MVP[0][0]);
	glUniform2fv(wh_VectorID, 1, &wh[0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		VERTEX_POSITION,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		VERTEX_COLOR,
		4,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glDrawElements(GL_TRIANGLES, N_vertex, GL_UNSIGNED_BYTE, (GLvoid*)0);
	alpha += 0.005;
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();
	DrawBackground();
	DrawBox();

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

