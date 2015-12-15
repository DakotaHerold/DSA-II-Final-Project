#pragma once
#include <iostream>
#include <SOIL.h>
#include <vector>
#include "ShaderHelpers.h"
#include <glm\glm.hpp> 
#include <glm\gtx\transform.hpp>
#include <glew.h>
#define GLFW_INCLUDE_GLU
#include <glfw3.h>
#include "SOIL.h"
using namespace std;
using namespace glm;

class Shape
{
public:
	Shape(void);
	~Shape(void);
	//Shape(GLfloat verts[], GLsizei vertCount, GLuint programIndex, bool h);
	Shape(vector<vec3> verts, GLsizei vertCount, vector<vec3> normals, vector<vec2> uvs, string tex, GLuint programIndex);
	void setWorldMatrix(const mat4 &matrix);
	void Draw(float x, float y, float xScale, float yScale);
	void Draw(vec3 pos, vec3 scalar, vec3 axis, float angle);
	GLuint index;
	bool wandering;


private:
	GLuint VBO;
	GLuint VAO;
	GLsizei numVertices;
	GLint offset;
	GLint s1;

	GLuint pos;
	GLuint rotation;
	GLint matrixLoc;
	mat4 matrix;


	bool hex;
};



