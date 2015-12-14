#include "Shape.h"
#include <iostream>
#include "ShaderHelpers.h"
#include <glm\glm.hpp> 
#include <glm\gtx\transform.hpp>
#include <glew.h>
#define GLFW_INCLUDE_GLU
#include <glfw3.h>
using namespace std;
using namespace glm;


Shape::Shape(void)
{
}


Shape::~Shape(void)
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

//Shape::Shape(GLfloat verts[], GLsizei vertCount, GLuint programIndex, bool h)
//{
//	numVertices = vertCount;
//	index = programIndex;
//	hex = h;
//
//
//	VAO = 1;
//	VBO = 1;
//
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	//calc size of array
//	GLfloat size = sizeof(GLfloat) * numVertices;
//
//	//bind VBO
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, 0); //parameter five is * floatsPerVert to seperate by- used to have sizeof(GL_FLOAT)* 2 as 5 th param
//	glEnableVertexAttribArray(0);
//
//
//	//call attrib pointer for colors
//	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)(sizeof(GL_FLOAT) * 2));
//			//glEnableVertexAttribArray(0); 
//	//glEnableVertexAttribArray(1);
//
//	matrixLoc = glGetUniformLocation(index, "worldMatrix");
//}

Shape::Shape(vector<vec3> verts, GLsizei vertCount, vector<vec3> normals, vector<vec2> uvs, GLuint programIndex)
{
	numVertices = vertCount;
	index = programIndex;


	//VAO = 1;
	VBO = 1;



	//calc size of array
	GLfloat size = sizeof(vec3) * numVertices;

	//bind VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, &verts[0], GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(vec3),                  // stride
		(void*)0            // array buffer offset
		);
	glEnableVertexAttribArray(0);


	//TEXTURE

	GLuint texturebuffer;
	glGenBuffers(1, &texturebuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texturebuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);


	//Get texture data into the texture sampler
	GLuint texID = SOIL_load_OGL_texture(
		"archer.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);




	//Getting texture coordinate off the buffer 
	glVertexAttribPointer(
		1,				//attrib number in shader 
		2,				//size
		GL_FLOAT,		//type?
		GL_FALSE,		//normalized?
		sizeof(vec2), //* Amount of floats per vertex --- stride //sizeof(GL_FLOAT)* 8
		(void*)(0)	//array buffer offset  (void*)(sizeof(GL_FLOAT)* 3)
		);
	glEnableVertexAttribArray(1);





	//LIGHTING

	//gen buffer -- Goes with commented vertex pointer
	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);

	//glVertexAttribPointer(
	//	2,				//attrib number in shader
	//	3,				//size
	//	GL_FLOAT,		//type?
	//	GL_FALSE,		//normalized?
	//	sizeof(GL_FLOAT)* 8, //* Amount of floats per vertices 
	//	(void*)(sizeof(GL_FLOAT)*5)		//array buffer offset 
	//	); //

	glVertexAttribPointer(
		2,				//attrib number in shader
		3,				//size
		GL_FLOAT,		//type?
		GL_FALSE,		//normalized?
		0, // stride 
		(void*)(0)		//array buffer offset 
		);


	glEnableVertexAttribArray(2);



	matrixLoc = glGetUniformLocation(index, "worldMatrix");

}


void Shape::Draw(vec3 pos, vec3 scalar, vec3 axis, float angle)
{

	//program the world matrix
	matrix = translate(pos)  * scale(scalar) *  rotate(angle, axis);

	setWorldMatrix(matrix);
	// Draw the triangle/Model !
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);

	//glDisableVertexAttribArray(0); 


}

void Shape::setWorldMatrix(const mat4 &matrix)
{
	glProgramUniformMatrix4fv(index, matrixLoc, 1, GL_FALSE, &matrix[0][0]);
}


