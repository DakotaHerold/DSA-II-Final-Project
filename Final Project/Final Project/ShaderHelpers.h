#pragma once
#include <iostream>
#include <glm\glm.hpp> 
#include <glm\gtx\transform.hpp>
#include <glew.h> 
#define GLFW_INCLUDE_GLU
#include <glfw3.h>
using namespace glm;

class ShaderHelpers
{
public:
	ShaderHelpers(void);
	~ShaderHelpers(void);
	char* loadTextFile(const char* file);
	GLuint loadShader(const  char* file, GLenum shaderType);
	GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile);
	void setShaderVec2(GLuint p, const char* name, vec2 vecToSend);
	void setShaderColor(GLuint programIndex, const char* uniformVar, float redVal, float blueVal, float greenVal);
};

