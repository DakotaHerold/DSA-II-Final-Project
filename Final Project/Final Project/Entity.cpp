#include "Entity.h"
#include <iostream>
#include "ShaderHelpers.h"
#include "Shape.h"
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

Entity::Entity(void)
{
}


Entity::~Entity(void)
{
}

Entity::Entity(Shape* s, vec3 cp, vec3 scale1, vec3 axis, float rotationAmt, float rotationSpeed)
{
	shape = s;
	currentPos = cp;
	active = false;
	scalar = scale1;
	rotationAxis = axis;
	rotationAmount = rotationAmt;
	rotSpeed = rotationSpeed;

	//setup physics 
	mass = 1.0f;
	acceleration = vec3(0.0f, 0.0f, 0.0f);
	velocity = vec3(0.0f, 0.0f, 0.0f);

	helper.loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	previousTime = 0;

	//calculate minimum bounding box - this needs to go in shape or entity 
	/*float xmin = INT_MAX;
	float ymin = INT_MAX;
	float zmin = INT_MAX;
	float xmax = INT_MIN;
	float ymax = INT_MIN;
	float zmax = INT_MIN;

	vector<float> xVals;
	vector<float> yVals;
	vector<float> zVals;*/

	//calculate xmin, ymin, xmax, ymax; 
	//populate vectors 
	//for (int i = 0; i < vertices.size(); i++)
	//{
	//	xVals.push_back(vertices[i].x);
	//	yVals.push_back(vertices[i].y);
	//	zVals.push_back(vertices[i].z);
	//}

	//// xVals for BB
	//for (int i = 0; i < xVals.size(); i++)
	//{
	//	if (xVals[i] < xmin)
	//	{
	//		xmin = xVals[i];
	//	}

	//	if (xVals[i] > xmax)
	//	{
	//		xmax = xVals[i];
	//	}
	//}

	//// yVals for BB
	//for (int i = 0; i < yVals.size(); i++)
	//{
	//	if (yVals[i] < ymin)
	//	{
	//		ymin = yVals[i];
	//	}

	//	if (yVals[i] > ymax)
	//	{
	//		ymax = yVals[i];
	//	}
	//}

	//// zVals for BB
	//for (int i = 0; i < zVals.size(); i++)
	//{
	//	if (zVals[i] < zmin)
	//	{
	//		zmin = zVals[i];
	//	}

	//	if (zVals[i] > zmax)
	//	{
	//		zmax = zVals[i];
	//	}
	//}

	//cout << "Values calculated from .obj" << endl;
	//cout << endl;
	//cout << "X min: " << xmin << endl;
	//cout << "Y min: " << ymin << endl;
	//cout << "Z min: " << zmin << endl;
	//cout << "X max: " << xmax << endl;
	//cout << "Y max: " << ymax << endl;
	//cout << "Z max: " << zmax << endl;
	//cout << endl;

	////create bounding vertices based on points
	//vector<vec3> box;
	//box.push_back(vec3(xmin, ymin, zmin));
	//box.push_back(vec3(xmax, ymin, zmin));
	//box.push_back(vec3(xmin, ymax, zmin));
	//box.push_back(vec3(xmin, ymin, zmax));
	//box.push_back(vec3(xmin, ymax, zmax));
	//box.push_back(vec3(xmax, ymin, zmax));
	//box.push_back(vec3(xmax, ymax, zmin));
	//box.push_back(vec3(xmax, ymax, zmax));

	////OBB 
	////output 
	////cout << "Oriented Bounding Box Vertices " << endl; 
	//for (int i = 0; i < box.size(); i++)
	//{
	//	/*cout << endl;
	//	cout << "X: " << box[i].x << " Y: " << box[i].y << " Z: " << box[i].z << endl;
	//	cout << endl;*/
	//}


	//BoundingBox A(vec3(0.0f, 0.0f, 0.0f), box, mat4(1));
}

void Entity::Update()
{
	cout << "Updating Entity" << endl;
	float currentTime = glfwGetTime();
	float dt = currentTime - previousTime;
	previousTime = currentTime;

	//add acceleration to velocity 
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;
	velocity.z += acceleration.z;
	//add velocity to position with dt
	currentPos.x += dt * velocity.x;
	currentPos.y += dt * velocity.y;
	currentPos.z += dt * velocity.z;

	//check for walls
	/*if (currentPos.x > 1.0f)
	{
	currentPos.x = -1.0f;
	velocity.x = 0.0f;
	}
	else if (currentPos.x < -1.1f)
	{
	currentPos.x = 1.0f;
	velocity.x = 0.0f;
	}


	if (currentPos.y > 1.0f)
	{
	currentPos.y = -1.0f;
	velocity.y = 0.0f;
	}
	else if (currentPos.y < -1.1f)
	{
	currentPos.y = 1.0f;
	velocity.y = 0.0f;
	}*/

	//reset acceleration
	acceleration = vec3(0.0f, 0.0f, 0.0f);

	//rotate if at all
	rotationAmount += dt * rotSpeed;
}

void Entity::Draw()
{
	cout << "Drawing Entity." << endl;
	shape->Draw(currentPos, scalar, rotationAxis, rotationAmount);
}

void Entity::AddForce(vec3 force)
{
	vec3 ftemp = force / mass;
	acceleration.x += force.x;
	acceleration.y += force.y;
	acceleration.z += force.z;
}


vec3 Entity::Seek(vec3 target, float mag)
{
	vec3 desired;
	desired.x = target.x - currentPos.x;
	desired.y = target.y - currentPos.y;
	desired.z = target.z - currentPos.z;

	//set magnitude here on desired
	desired = normalize(desired) * mag;

	//steer 
	vec3 steer;
	steer.x = desired.x - velocity.x;
	steer.y = desired.y - velocity.y;
	steer.z = desired.z - velocity.z;

	//check if on target
	//get distance between the two

	if (shape->wandering == false)
	{
		float lengthBetween = length(desired);
		if (lengthBetween < 0.01f)
		{
			velocity = vec3(0, 0, 0);
			return vec3(0, 0, 0);
		}
		else
		{
			return steer;
		}
	}
	else
	{
		return steer;
	}
}

vec3 Entity::Arrive(vec3 target)
{
	vec3 desired = target - currentPos;

	//set magnitude here on desired
	//desired = normalize(desired) * mag;  

	vec3 maxV = vec3(0.4f, 0.4f, 0.0f);

	float distance = length(desired);
	float slowingRadius = 0.001f;
	// Check the distance to detect whether the character
	//Arrived
	if (distance == 0.0f)
	{
		currentPos = target;
		velocity = vec3(0, 0, 0);
	}
	// is inside the slowing area
	else if (distance < slowingRadius) {
		// Inside the slowing area
		desired = normalize(desired) * maxV * (distance / slowingRadius);
	}
	else
	{
		// Outside the slowing area.
		desired = normalize(desired) * maxV;
	}

	//steer 
	vec3 steer;
	steer.x = desired.x - velocity.x;
	steer.y = desired.y - velocity.y;
	steer.z = desired.z - velocity.z;

	return steer;
}

vec3 Entity::Flee(vec3 target, float mag)
{
	vec3 desired;
	desired.x = currentPos.x - target.x;
	desired.y = currentPos.y - target.y;
	desired.z = currentPos.z - target.z;

	//set magnitude here on desired
	desired = normalize(desired) * mag;


	//steer 
	vec3 steer;
	steer.x = desired.x - velocity.x;
	steer.y = desired.y - velocity.y;
	steer.z = desired.z - velocity.z;

	return steer;
}

vec3 Entity::Wander()
{
	float wanderR = 0.001f;         // Radius for our "wander circle"
									//    float wanderD = 0.1f;         // Distance for our "wander circle"
	float changeh = 0.03f;
	float changel = 0.001f;
	float wandertheta = changel + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (changeh - changel)));

	//get normal 
	float magnitude = velocity.length();
	vec3 normal;
	normal.x = velocity.x / magnitude;
	normal.y = velocity.y / magnitude;
	normal.z = 0;

	//	normal * wanderD;  

	//make relative to location
	currentPos.x += normal.x;
	currentPos.y += normal.y;

	float headingAngle = (float)atan2(normal.y, normal.x);

	vec3 offset = vec3(wanderR*cos(wandertheta + headingAngle), wanderR*sin(wandertheta + headingAngle), 0.0f); //create an offset 
	vec3 target;
	target.x = currentPos.x + offset.x;
	target.y = currentPos.y + offset.y;
	target.z = 0.0f;
	//add arbitrary magnitude 
	vec3 result = Seek(target, 0.009f);

	return result;

}


vec3 Entity::getCurrentPos()
{
	return currentPos;
}

void Entity::setCurrentPos(float nx, float ny, float nz)
{
	currentPos.x = nx;
	currentPos.y = ny;
	currentPos.z = nz;
}

void Entity::setCurrentPos(vec3 newPos)
{
	currentPos = newPos;
}

float Entity::getMass()
{
	return mass;
}

vec3 Entity::getAcceleration()
{
	return acceleration;
}

vec3 Entity::getVelocity()
{
	return velocity;
}

void Entity::setVelocity(vec3 v)
{
	velocity = v;
}

void Entity::setRotationSpeed(float speed)
{
	rotSpeed = speed;
}

bool Entity::isActive()
{
	return active;
}

void Entity::setActive(bool a)
{
	active = a;
}
