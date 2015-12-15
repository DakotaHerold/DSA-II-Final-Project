#pragma once
#include <iostream>
#include "ShaderHelpers.h"
#include "Shape.h"
#include "BoundingBox.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <glm\glm.hpp> 
#include <glm\gtx\transform.hpp>
#include <glew.h>
#define GLFW_INCLUDE_GLU
#include <glfw3.h>
using namespace std;
using namespace glm;

class Entity
{
public:
	Entity(void);
	~Entity(void);
	Entity(Shape* s, vec3 cp, vec3 scale1, vec3 axis, float rotationAmt, float rotationSpeed, vector<vec3> modelVerts);
	void AddForce(vec3 force);
	vec3 Seek(vec3 target, float mag);
	vec3 Arrive(vec3 target);
	vec3 Flee(vec3 target, float mag);
	vec3 Wander();
	void Update();
	void Draw();
	void setRotationSpeed(float speed);
	void printOBB(); 
	 
	//getters
	float getMass();
	bool isActive();
	vec3 getAcceleration();
	vec3 getVelocity();
	vec3 getCurrentPos();
	//setters
	void setCurrentPos(float nx, float ny, float nz);
	void setCurrentPos(vec3 newPos);
	void setActive(bool a);
	void setVelocity(vec3 v);
	bool active;

	//BoundingBox 
	BoundingBox* boundingBox; 
	vector<vec3> modelVertices; 

private:
	Shape* shape;
	vec3 currentPos;
	vec3 scalar;
	vec3 rotationAxis;
	float rotationAmount;
	ShaderHelpers helper;
	float previousTime;
	float rotSpeed;

	float mass;
	vec3 acceleration;
	vec3 velocity;

};



