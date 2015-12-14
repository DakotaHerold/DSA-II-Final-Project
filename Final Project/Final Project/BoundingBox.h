#pragma once
#include <vector>
#include <glm\glm.hpp> 
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>
using namespace std;
using namespace glm;


class BoundingBox
{
public:
	BoundingBox(vec3 pos, vector<vec3> boxVerts, mat4 &mMatrix);
	~BoundingBox();
	void setPos(vec3 newPos); 

	//attributes 
	vec3 position;
	mat4 modelMatrix;
	vec4 xAxis;
	vec4 yAxis;
	vec4 zAxis;
	
	//box verts
	vector<vec3> box; 

	//center
	vec3 centroid;
	//half widths
	float e0_Dc; //depth 
	float e1_Hc; //height 
	float e2_Wc; //width 

};

