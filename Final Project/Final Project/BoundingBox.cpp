#include "BoundingBox.h"


BoundingBox::BoundingBox(vec3 pos, vector<vec3> boxVerts, mat4 &mMatrix)
{
	//set pos 
	position = pos;

	box = boxVerts; 

	//find centroid 
	/*for (int i = 0; i < box.size(); i++)
	{
		centroid += box[i];
	}
	centroid = centroid / (float)box.size();
	centroid *= position;
	if (centroid.x == 0.0f && centroid.y == 0.0f && centroid.z == 0.0f)
	{
		centroid = position; 
	}*/
	centroid = position; 

	//default rotation matrix 
	mat4 modelMatrix = mMatrix;

	//directional vectors u from centroid 
	xAxis = vec4(1, 0, 0, 0) * modelMatrix;
	yAxis = vec4(0, 1, 0, 0) * modelMatrix;
	zAxis = vec4(0, 0, 1, 0) * modelMatrix;




	//find half widths of each vector 

	//vec3(xmax, ymax, zmax) - vec3(xmax, ymax, zmin) --- Depth half width 

	vec3 e0vec = boxVerts[7] - boxVerts[6];
	e0_Dc = length(e0vec) / 2;

	// vec3(xmin, ymax, zmin) - vec3(xmin, ymin, zmin) --- Height half width 
	vec3 e2vec = boxVerts[2] - boxVerts[0];
	e2_Wc = length(e2vec) / 2;

	//vec3(xmax, ymin, zmin) - vec3(xmin, ymin, zmin) --- Width half width 
	vec3 e1vec = boxVerts[1] - boxVerts[0];
	e1_Hc = length(e1vec) / 2;

	//Don't half to find half widths of Maya primitives, it is always 0.5f 
	e0_Dc = 0.4f; 
	e1_Hc = 0.4f; 
	e2_Wc = 0.4f; 
}

void BoundingBox::setPos(vec3 newPos)
{
	//set new position
	position = newPos;
	//recalc centroid 
	//find centroid 
	/*for (int i = 0; i < box.size(); i++)
	{
		centroid += box[i];
	}
	centroid = centroid / (float)box.size();
	centroid *= position;*/
	centroid = position; 

}


BoundingBox::~BoundingBox()
{
}
