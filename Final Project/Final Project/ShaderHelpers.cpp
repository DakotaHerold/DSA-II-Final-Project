#include "ShaderHelpers.h"
#include <fstream> 
#include <iostream> 
#include <glm\glm.hpp> 
#include <glm\gtx\transform.hpp>
using namespace std;
using namespace glm;


ShaderHelpers::ShaderHelpers(void)
{
}


ShaderHelpers::~ShaderHelpers(void)
{
}

char* ShaderHelpers::loadTextFile(const char* file)
{
	//create stream
	ifstream stream(file, ios::binary);

	if (stream.is_open())
	{
		//array to store in 
		char* text;

		//determine length
		int length;
		//go to end
		stream.seekg(0, ios::end);
		length = (int)stream.tellg();

		//move back to beginning 
		stream.seekg(0, ios::beg);

		//actually read and set null pointer 
		text = new char[length + 1];
		text[length] = 0;

		stream.read(text, length);
		return text;
	}
	else
	{
		cout << "Could not find or could not open file. " << endl;
		return 0;
	}
}

GLuint ShaderHelpers::loadShader(const  char* file, GLenum shaderType)
{

	const char* text;
	if (loadTextFile(file) != 0)
	{
		text = loadTextFile(file);
		//create the vertex shader
		GLuint index = glCreateShader(shaderType);
		//params should be (shader obj index, how many strings make up the code, address of one or more strings(the actual code), actual string sizes - 0 if null terminated)
		glShaderSource(index, 1, &text, 0);
		//takes index
		glCompileShader(index);
		//check if shader compiles
		GLint compiles;
		//takes obj index, info - correct, address to store
		glGetShaderiv(index, GL_COMPILE_STATUS, &compiles);
		if (compiles == GL_FALSE)
		{
			//log errors 
			GLint loglength;
			glGetShaderiv(index, GL_INFO_LOG_LENGTH, &loglength);
			//there is an error so figure out what it is
			if (loglength > 1)
			{
				char* log = new char[loglength + 1];
				glGetShaderInfoLog(index, loglength, 0, log);
				cout << "Log found for shader: " << log << endl;

				glDeleteShader(index);
				delete[] log;
				return 0;
			}
		}
		//clean up
		delete[] text;
		//everything worked. 
		return index;

	}
	else
	{
		cout << "Problem loading shader" << endl;
		return 0;
	}


}

GLuint ShaderHelpers::loadShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	//vert shader
	GLuint shader1 = loadShader(vertexFile, GL_VERTEX_SHADER);
	if (shader1 == 0)
	{
		return 0;
	}

	//frag shader
	GLuint shader2 = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	if (shader2 == 0)
	{
		return 0;
	}

	//create shader program
	GLuint program = glCreateProgram();
	glAttachShader(program, shader1);
	glAttachShader(program, shader2);
	//link
	glLinkProgram(program);

	//check to see if linked
	GLint compiles;
	glGetProgramiv(program, GL_LINK_STATUS, &compiles);
	if (compiles == GL_TRUE)
	{
		return program;
	}
	else if (compiles == GL_FALSE)
	{
		//log errors 
		GLint loglength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &loglength);
		//there is an error so figure out what it is
		if (loglength > 1)
		{
			char* log = new char[loglength + 1];
			glGetProgramInfoLog(program, loglength, 0, log);
			cout << "Log found for program: " << log << endl;

			glDeleteProgram(program);
			delete[] log;
			return 0;
		}
	}
}


void ShaderHelpers::setShaderColor(GLuint programIndex, const char* uniformVar, float redVal, float blueVal, float greenVal)
{
	GLuint uniformIndex;
	uniformIndex = glGetUniformLocation(programIndex, uniformVar);
	if (uniformIndex == -1)
	{
		cout << "Could not set color from shader..." << endl;
	}
	else
	{
		//cout << "Color set by shader..." << endl;
	}

	glProgramUniform4f(programIndex, uniformIndex, redVal, blueVal, greenVal, 1.0f);
	//glProgramUniform3f(programIndex, uniformIndex, redVal, blueVal, greenVal);
}

void ShaderHelpers::setShaderVec2(GLuint p, const char* name, vec2 vecToSend)
{
	GLuint uniformIndex = glGetUniformLocation(p, name);
	if (uniformIndex == -1)
	{
		cout << "setShaderVec2 color could not find." << endl;
	}

	glProgramUniform2fv(p, uniformIndex, 1, &vecToSend[0]);
}