#pragma once
#include <gl/glew.h> // http://glew.sourceforge.net/
#include <gl/wglew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GLRenderer
{
	GLuint programID;
	GLuint MatrixID;
	GLuint Texture;
	GLuint TextureID;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint VertexArrayID;
public:
	GLRenderer();
	void init();
	void Draw();
	~GLRenderer();
};

