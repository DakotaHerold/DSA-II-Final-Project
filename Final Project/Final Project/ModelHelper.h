#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <glm\glm.hpp> 
#include <glm\gtx\transform.hpp>
#include <glew.h> 
#include <sstream>
#define GLFW_INCLUDE_GLU
#include <glfw3.h>
using namespace glm;
using namespace std;


class ModelHelper
{
public:
	ModelHelper();
	~ModelHelper();
	bool loadModelFile(const char* infile, vector<vec3> &out_vertices, vector<vec2> &out_uvs, vector<vec3> &out_normals); //returns false if something went wrong
	bool loadModelFile(const string infile, vector<vec3> &out_vertices, vector<vec2> &out_uvs, vector<vec3> &out_normals);
};

