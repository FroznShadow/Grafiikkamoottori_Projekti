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
#include "Circle.h"
#include "Matikka.h"
#include "vertexshader.h"
namespace Renderer
{
	void Render();
	int Init(void);
	int InitCamera(void);
	int initBackground(void);
	int InitBox(void);
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

}
namespace
{
	//GLFWwindow* window;
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


	//float alpha = 1.0f;

	GLfloat cameraX = 0.0f, cameraY = 0.0f;
	//glm::mat4 MVP(1.0);
	glm::vec2 wh;
	int N_triangles;
	int N_vertex;
	int error_code;

	int num;
	int w;
	int h;
}
	void Renderer::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		wh = glm::vec2(width, height);
		//std::cout<<width<<"x"<<height<<" "<<w<<"x"<<h<<"\n";
	}
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

		textureProgramID = LoadShaders("Texture.VertexShader", "Texture.FragmentShader");
		static const GLfloat texture_vertex_buffer_data[] =
		{
			-1.0, -1.0, 0.9,
			1.0, -1.0, 0.9,
			-1.0, 1.0, 0.9,
			1.0, 1.0, 0.9,
		};
		glGenBuffers(1, &textureVertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, textureVertexbuffer);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(texture_vertex_buffer_data), texture_vertex_buffer_data, GL_STATIC_DRAW);
		static const GLubyte texture_indices[] =
		{
			0, 1, 2, 
			1, 3, 2,
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
		Texture = loadBMP_custom("./uvtemplate.bmp");
		return 0;
	}

	int InitBox(void)
	{
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		programID = LoadShaders("VertexShader.vertexshader", "FragmentShader.fragmentshader");
		MVP_MatrixID = glGetUniformLocation(programID, "MVP");
		wh_VectorID = glGetUniformLocation(programID, "wh");

#define SQRT05 0.707
		static GLfloat g_vertex_buffer_data[] = {

			0.0f, 0.0f, 0.0f, //0
			1.0f, 0.0f, 0.0f, //1
			SQRT05, SQRT05, 0.0f, //2
			0.0f, 1.0f, 0.0f,//3
			-SQRT05, SQRT05, 0.0f,//4
			-1.0f, 0.0f, 0.0f, //5
			-SQRT05, -SQRT05, 0.0f,//6
			0.0f, -1.0f, 0.0f, //7
			SQRT05, -SQRT05, 0.0f, //8
		};
		static GLuint g_indices[] = {
			0, 1, 2, //1
			0, 2, 3, //2
			0, 3, 4, //3
			0, 4, 5, //4
			0, 5, 6, //5
			0, 6, 7, //6
			0, 7, 8, //7
			0, 8, 1, //8
		};


		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


		static const GLfloat g_color_buffer_data[] = {
			1.0f, 0.0f, 0.0f, 1.0f, //0
			0.0f, 1.0f, 0.0f, 0.5f, //1
			0.0f, 0.0f, 1.0f, 0.5f, //2
			0.1f, 1.0f, 1.0f, 1.0f, //3
			1.0f, 0.0f, 0.0f, 1.0f, //4
			0.0f, 1.0f, 0.0f, 0.5f, //5
			0.0f, 0.0f, 1.0f, 0.5f, //6
			0.1f, 1.0f, 1.0f, 1.0f, //7
			0.1f, 1.0f, 1.0f, 1.0f, //8
		};

		glGenBuffers(1, &colorbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

		glGenBuffers(1, &indexbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), g_indices, GL_STATIC_DRAW);

		N_vertex = sizeof(g_indices) / sizeof(*g_indices);
	
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

	int w = 640;
	int h = 480;
	window = glfwCreateWindow(w, h, "Graphics Engine", NULL, NULL);
	if (window == NULL)
	{
		error_code = 102;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Renderer::FramebufferSizeCallback);
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		error_code = 103;
		return -1;
	}
	InitCamera();
	InitBackground();

	glClearColor(0.25f, 0.25f, 0.25f, 0.0f);
	
	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	InitBox();
	


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
		3, 
		GL_FLOAT, 
		GL_FALSE,
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

	RotateMath();
	glUseProgram(programID);
	

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	//DrawBox();
	//DrawBackground();
	Triforce(num);
	DrawBox();
	DrawCircle();
	
	glfwSwapBuffers(window);
}
void Uninit(void)
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteBuffers(1, &textureVertexbuffer);
	glDeleteBuffers(1, &textureIndexbuffer);
	
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
	glDeleteProgram(textureProgramID);
}

