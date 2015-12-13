#pragma once
#include <iostream>
#include "ShaderHelpers.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm\glm.hpp> 
#include <glm\gtx\transform.hpp>
#include <glew.h>
#include <vector>
#define GLFW_INCLUDE_GLU
#include <glfw3.h>
using namespace std;
using namespace glm;

class ProceduralModels
{
public:
	ProceduralModels();
	~ProceduralModels();
	void makeTorus(int iMax, int jMax);
	vec3 torusV(float t, float p);
	void addQuad(vec3 a, vec2 uvA, vec3 b, vec2 uvB, vec3 c, vec2 uvC, vec3 d, vec2 uvD);
	void addTriangle(vec3 a, vec2 uvA, vec3 b, vec2 uvB, vec3 c, vec2 uvC);
	vec3 getNormal(vec3 a, vec3 b, vec3 c);
	void makeCube(float s);
	void makeSphere(float slices, float stacks, float radius);
	void makeCylinder(float slices, float radius);


	vector<vec3> positions;
	vector<vec2> uvs;
	vector<vec3> normals;
	vector<vec3> elements;

	inline float binomialCoefficient(float n, float k)
	{
		int i;
		float b;
		if (0 == k || n == k) {
			return 1.0f;
		}
		if (k > n) {
			return 0.0f;
		}

		if (1 == k) {
			return n;
		}
		b = 1.0f;
		for (i = 1; i <= k; i++) {
			b *= (n - (k - i));
			if (b < 0) return -1;
			b /= i;
		}
		return b;
	}

	inline float bernsteinPolynomial(float i, float n, float u)
	{
		return binomialCoefficient(n, i) * pow(u, i) * pow(1 - u, n - i);
	}

	inline vec3 bezierSurface(float u, float v, vector<vector<vec3>> k)
	{
		vec3 p = vec3();

		//Iterate over the control points kij
		int n = k.size() - 1;
		int m = k[0].size() - 1;
		float poly1, poly2;
		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= m; j++)
			{
				poly1 = bernsteinPolynomial(i, n, u);
				poly2 = bernsteinPolynomial(j, m, v);
				p += k[i][j] * poly1 * poly2;
			}
		}
		return p;
	}

	void makeBezierSurface(float u, float v, vector<vector<vec3>> k);
};

