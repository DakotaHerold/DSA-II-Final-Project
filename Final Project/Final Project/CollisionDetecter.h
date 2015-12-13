#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <glm\glm.hpp> 
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>
#include "BoundingBox.h"
#define _USE_MATH_DEFINES

using namespace std;
using namespace glm;


class CollisionDetecter
{
public:
	CollisionDetecter();
	~CollisionDetecter();
	bool SAT(BoundingBox &A, BoundingBox &B);
};

