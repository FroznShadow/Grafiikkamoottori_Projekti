#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include <GLFW\glfw3.h>

//loadBMP
GLuint textureID;
//Generate
GLuint Width, Height;
GLuint Internal_Format;
GLuint Image_Format;

GLuint Wrap_S;
GLuint Wrap_T;
GLuint Filter_Min;
GLuint Filter_Max;

GLuint loadBMP_custom(GLuint width, GLuint height, const char * imagepath)
{
	glGenTextures(1 ,&textureID);

	//Generate
	Width = width;
	Height = height;

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, imagepath);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max);

	glBindTexture(GL_TEXTURE_2D, 0);


	//Bind
	glBindTexture(GL_TEXTURE_2D, textureID);



	return textureID;
}


/*
GLuint Generate(GLuint width, GLuint height, unsigned char* data)
{

	Width = width;
	Height = height;

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max);

	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}

GLuint Bind() 
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	return textureID;

}
*/
