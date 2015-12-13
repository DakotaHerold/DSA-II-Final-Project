#pragma once
#include "Shape.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ShaderHelpers.h"
#include <glm\glm.hpp> 
#include <glm\gtx\transform.hpp>
#include <glm\gtx\wrap.hpp>
#include <glew.h>
#define GLFW_INCLUDE_GLU
#include <glfw3.h>
using namespace std;
using namespace glm;

class Camera
{
public:
	Camera();
	~Camera();
	void turn(float dx, float dy);
	void move(vec3 movement);
	void setLocation(vec3 p);
	vec3 getLocation();
	vec3 getForward();
	vec3 getLookAt();
	vec3 getUp();
	vec3 getRight();
	vec3 normalizeVec(const vec3 &v);
	float yaw;
	float pitch;
	vec3 pos;
};

