#include "ProceduralModels.h"


ProceduralModels::ProceduralModels()
{
}


ProceduralModels::~ProceduralModels()
{
}

void ProceduralModels::makeTorus(int iMax, int jMax)
{
	for (int i = 0; i < iMax; i++)
	{
		//Theta for this i
		float uA = 1 - (float)i / (float)iMax;
		float tA = 2.0 * M_PI *uA;
		//Theta for next i
		float uB = 1 - (float)(i + 1) / (float)iMax;
		float tB = 2.0 * M_PI * uB;

		for (int j = 0; j < jMax; j++)
		{
			//Phi for this j
			float vA = (float)j / (float)jMax;
			float pA = 2.0 * M_PI * vA;
			//Phi for next j
			float vC = (float)(j + 1) / (float)jMax;
			float pC = 2.0 * M_PI * vC;

			vec3 a = torusV(tA, pA);
			vec3 b = torusV(tB, pA);
			vec3 c = torusV(tA, pC);
			vec3 d = torusV(tB, pC);

			vec2 uvA = vec2(uA, vA);
			vec2 uvB = vec2(uB, vA);
			vec2 uvC = vec2(uA, vC);
			vec2 uvD = vec2(uB, vC);

			addQuad(b, uvB, a, uvA, d, uvD, c, uvC);
		}
	}
}

vec3 ProceduralModels::torusV(float t, float p)
{
	float R = 0.7f;
	float r = 0.3f;

	float x = ((R + r* cosf(t)) * cosf(p));
	float y = ((R + r* cosf(t)) * sinf(p));
	float z = r*sinf(t);

	return vec3(x, y, z);
}

void ProceduralModels::addQuad(
	vec3 a, vec2 uvA,
	vec3 b, vec2 uvB,
	vec3 c, vec2 uvC,
	vec3 d, vec2 uvD
	)
{
	/*
	_____
	|   /|
	|  / |
	| /  |
	|/   |
	------
	*/


	//Triangle 1
	addTriangle(a, uvA, b, uvB, c, uvC);

	//Triangle 2
	addTriangle(d, uvD, c, uvC, b, uvB);
}

void ProceduralModels::addTriangle(vec3 a, vec2 uvA, vec3 b, vec2 uvB, vec3 c, vec2 uvC)
{
	//Vertex A 
	positions.push_back(a);
	uvs.push_back(uvA);
	normals.push_back(getNormal(a, b, c));
	//elements.push_back(elements.size()); 

	//Vertex B
	positions.push_back(b);
	uvs.push_back(uvB);
	normals.push_back(getNormal(a, b, c));
	//elements.push_back(elements.size()); 

	//Vertex C
	positions.push_back(c);
	uvs.push_back(uvC);
	normals.push_back(getNormal(a, b, c));
	//elements.push_back(elements.size()); 

}

vec3 ProceduralModels::getNormal(vec3 a, vec3 b, vec3 c)
{
	vec3 lhs = c - a;
	vec3 rhs = b - a;

	vec3 normal = cross(lhs, rhs);
	return normal;
}

void ProceduralModels::makeBezierSurface(float uiMax, float viMax, vector<vector<vec3>> k)
{
	//Iterate over the surface
	int n = k.size() - 1;
	int m = k[0].size() - 1;
	for (int ui = 0; ui < uiMax; ui++)
	{
		for (int vi = 0; vi < viMax; vi++)
		{
			float u0 = (float)ui / (float)uiMax;
			float v0 = (float)vi / (float)viMax;

			float u1 = (float)(ui + 1) / (float)uiMax;
			float v1 = (float)(vi + 1) / (float)viMax;

			vec3 a = bezierSurface(u0, v0, k);
			vec2 uvA = vec2(u0, v0);
			vec3 b = bezierSurface(u1, v0, k);
			vec2 uvB = vec2(u1, v0);
			vec3 c = bezierSurface(u0, v1, k);
			vec2 uvC = vec2(u0, v1);
			vec3 d = bezierSurface(u1, v1, k);
			vec2 uvD = vec2(u1, v1);

			addQuad(a, uvA, b, uvB, c, uvC, d, uvD);
		}
	}
}

void ProceduralModels::makeCube(float s)
{
	//cube vertices 
	vector<vec3> cv;
	cv.push_back(vec3(-s, -s, -s)); // triangle 1 : begin
	cv.push_back(vec3(-s, -s, s));
	cv.push_back(vec3(-s, s, s)); // triangle 1 : end       
	cv.push_back(vec3(s, s, -s)); // triangle 2 : begin
	cv.push_back(vec3(-s, -s, -s));
	cv.push_back(vec3(-s, s, -s)); // triangle 2 : end 
	cv.push_back(vec3(s, -s, s));
	cv.push_back(vec3(-s, -s, -s));
	cv.push_back(vec3(s, -s, -s));
	cv.push_back(vec3(s, s, -s));
	cv.push_back(vec3(s, -s, -s));
	cv.push_back(vec3(-s, -s, -s));
	cv.push_back(vec3(-s, -s, -s));
	cv.push_back(vec3(-s, s, s));
	cv.push_back(vec3(-s, s, -s));
	cv.push_back(vec3(s, -s, s));
	cv.push_back(vec3(-s, -s, s));
	cv.push_back(vec3(-s, -s, -s));
	cv.push_back(vec3(-s, s, s));
	cv.push_back(vec3(-s, -s, s));
	cv.push_back(vec3(s, -s, s));
	cv.push_back(vec3(s, s, s));
	cv.push_back(vec3(s, -s, -s));
	cv.push_back(vec3(s, s, -s));
	cv.push_back(vec3(s, -s, -s));
	cv.push_back(vec3(s, s, s));
	cv.push_back(vec3(s, -s, s));
	cv.push_back(vec3(s, s, s));
	cv.push_back(vec3(s, s, -s));
	cv.push_back(vec3(-s, s, -s));
	cv.push_back(vec3(s, s, s));
	cv.push_back(vec3(-s, s, -s));
	cv.push_back(vec3(-s, s, s));
	cv.push_back(vec3(s, s, s));
	cv.push_back(vec3(-s, s, s));
	cv.push_back(vec3(s, -s, s));


	//uvs
	vector<vec2> cuvs;

	//set scale
	/*for (vec3 v : cv)
	{
	v.x *= s;
	v.y *= s;
	v.z *= s;
	}*/
	int counter = 0;
	for (int i = 0; i < cv.size(); i++)
	{
		counter++;
		if (counter == 3)
		{
			addTriangle(cv[i - 2], vec2(3 - i, 3 - i), cv[i - 1], vec2(3 - i, 3 - i), cv[i], vec2(3 - i, 3 - i));
			counter = 0;
		}
	}
}

void ProceduralModels::makeSphere(float slices, float stacks, float radius)
{
	//slices are horizontal
	//stacks are vertical 

	vec3 temp;
	vec3 temp1;
	vector<vec3> tempVecs = vector<vec3>();
	vector<vec3> tempVecs2 = vector<vec3>();
	for (int i = 0; i <= stacks; i++)
	{

		tempVecs = vector<vec3>();
		tempVecs2 = vector<vec3>();
		float V = i / (float)stacks;
		float phi = V * glm::pi <float>();


		float V1 = i + 1 / (float)stacks;
		float phi1 = V * glm::pi <float>();

		int counter = 0;
		// Loop Through Slices
		for (int j = 0; j <= slices; j++)
		{

			float U = j / (float)slices;
			float theta = U * (pi <float>() * 2);

			float U1 = j + 1 / (float)slices;
			float theta1 = U * (pi <float>() * 2);

			// Calc The Vertex Positions
			float x = cosf(phi) * sinf(theta);
			float y = sinf(theta) * sinf(phi);
			float z = cosf(theta);

			float x1 = cosf(phi) * sinf(theta);
			float y1 = sinf(theta) * sinf(phi);
			float z1 = cosf(theta);

			temp = vec3(x, y, z)*radius;
			tempVecs.push_back(temp);

			temp1 = vec3(x1, y1, z1)*radius;
			tempVecs2.push_back(temp1);
			counter++;

			if (counter == 2)
			{
				addQuad(tempVecs[1], vec2(0, 0), tempVecs[0], vec2(0, 0), tempVecs2[1], vec2(0, 0), tempVecs2[0], vec2(0, 0));

				//Triangle 1 - abc - 012
				//addTriangle(tempVecs[0], vec2(i, j), tempVecs[1], vec2(i, j), tempVecs[2], vec2(i, j));

				//Triangle 2 dcb - 321
				//addTriangle(tempVecs[2], vec2(i, j), tempVecs[1], vec2(i, j), tempVecs[0], vec2(i, j));


				counter = 0;
				tempVecs = vector<vec3>();
			}

		}
	}


}

void ProceduralModels::makeCylinder(float slices, float radius)
{
	//slices are horizontal
	//stacks are vertical 

	vec3 temp;
	vector<vec3> tempVecs = vector<vec3>();
	int counter = 0;

	for (int i = 0; i < slices; i++)
	{

		float theta = glm::pi<float>() / slices;
		// Calc The Vertex Positions
		float x = cosf(theta);
		float y = sinf(theta);
		float z = 1;

		vec3 temp = vec3(x, y, z) * radius;
		tempVecs.push_back(temp);
		counter++;
		if (counter == 4)
		{
			addQuad(tempVecs[1], vec2(0, 0), tempVecs[0], vec2(0, 0), tempVecs[3], vec2(0, 0), tempVecs[2], vec2(0, 0));
			tempVecs = vector<vec3>();
			counter = 0;
		}
	}


}