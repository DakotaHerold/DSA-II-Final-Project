#include "CollisionDetecter.h"


CollisionDetecter::CollisionDetecter()
{
}


CollisionDetecter::~CollisionDetecter()
{
}

bool CollisionDetecter::SAT(BoundingBox &A, BoundingBox &B)
{
	//1. Get edge
	//2. Get edge's normal vector 
	//3. Project each vertex on edge's normal vector 
	//4. Check, for each shape, projected vertex min & max intervals and see if they overlap
	//5. If intervals overlap, goto step 1, get next edge of the shapes. For collision, all edge and vertex projections must have overlapping intervals
	//6. if at least one interval doesn't overlap then not colliding 

	//see realtime collision book pg 103

	//compute translational vector T
	vec4 T = vec4((B.centroid - A.centroid), 0.0f);
	//max translational vector magnitude 
	float mtvMag = 1000000.f;
	vec4 mtvAxis = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	vec4 mtv = vec4(0.0f, 0.0f, 0.0f, 0.0f);


	if (abs(dot(T, A.xAxis)) > (A.e2_Wc
		+ abs(B.e2_Wc * dot(A.xAxis, B.xAxis))
		+ abs(B.e1_Hc * dot(A.xAxis, B.yAxis))
		+ abs(B.e0_Dc * dot(A.xAxis, B.zAxis))))
	{
		cout << "no intersection in a-x axis\n";
		return true;
	}
	else
	{
		if (mtvMag > (A.e2_Wc
			+ abs(B.e2_Wc * dot(A.xAxis, B.xAxis))
			+ abs(B.e1_Hc * dot(A.xAxis, B.yAxis))
			+ abs(B.e0_Dc * dot(A.xAxis, B.zAxis))))
		{
			mtvMag = (A.e2_Wc
				+ abs(B.e2_Wc * dot(A.xAxis, B.xAxis))
				+ abs(B.e1_Hc * dot(A.xAxis, B.yAxis))
				+ abs(B.e0_Dc * dot(A.xAxis, B.zAxis)));

			mtvAxis = A.xAxis;

		}
	}

	// box A y-axis
	if (abs(dot(T, A.yAxis)) > (A.e1_Hc
		+ abs(B.e2_Wc * dot(A.yAxis, B.xAxis))
		+ abs(B.e1_Hc * dot(A.yAxis, B.yAxis))
		+ abs(B.e0_Dc * dot(A.yAxis, B.zAxis))))
	{
		std::cout << "no intersection in a-y axis\n";
		return true;
	}
	else
	{
		if (mtvMag > (A.e1_Hc
			+ abs(B.e2_Wc * dot(A.yAxis, B.xAxis))
			+ abs(B.e1_Hc * dot(A.yAxis, B.yAxis))
			+ abs(B.e0_Dc * dot(A.yAxis, B.zAxis))))
		{
			mtvMag = (A.e1_Hc
				+ abs(B.e2_Wc * dot(A.yAxis, B.xAxis))
				+ abs(B.e1_Hc * dot(A.yAxis, B.yAxis))
				+ abs(B.e0_Dc * dot(A.yAxis, B.zAxis)));

			mtvAxis = A.yAxis;

		}
	}

	// box A z-axis
	if (abs(dot(T, A.zAxis)) > (A.e0_Dc
		+ abs(B.e2_Wc * dot(A.zAxis, B.xAxis))
		+ abs(B.e1_Hc * dot(A.zAxis, B.yAxis))
		+ abs(B.e0_Dc * dot(A.zAxis, B.zAxis))))
	{
		cout << "no intersection in a-z axis\n";
		return true;
	}
	else
	{
		if (mtvMag > (A.e0_Dc
			+ abs(B.e2_Wc * dot(A.zAxis, B.xAxis))
			+ abs(B.e1_Hc * dot(A.zAxis, B.yAxis))
			+ abs(B.e0_Dc * dot(A.zAxis, B.zAxis))))
		{
			mtvMag = (A.e0_Dc
				+ abs(B.e2_Wc * dot(A.zAxis, B.xAxis))
				+ abs(B.e1_Hc * dot(A.zAxis, B.yAxis))
				+ abs(B.e0_Dc * dot(A.zAxis, B.zAxis)));

			mtvAxis = A.zAxis;

		}
	}

	// Box B x-axis
	if (abs(dot(T, B.xAxis)) > (B.e2_Wc
		+ abs(A.e2_Wc * dot(A.xAxis, B.xAxis))
		+ abs(A.e1_Hc * dot(A.yAxis, B.xAxis))
		+ abs(A.e0_Dc * dot(A.zAxis, B.xAxis))))
	{
		std::cout << "no intersection in b-x axis\n";
		return true;
	}
	else
	{
		if (mtvMag >  (B.e2_Wc
			+ abs(A.e2_Wc * dot(A.xAxis, B.xAxis))
			+ abs(A.e1_Hc * dot(A.yAxis, B.xAxis))
			+ abs(A.e0_Dc * dot(A.zAxis, B.xAxis))))
		{
			mtvMag = (B.e2_Wc
				+ abs(A.e2_Wc * dot(A.xAxis, B.xAxis))
				+ abs(A.e1_Hc * dot(A.yAxis, B.xAxis))
				+ abs(A.e0_Dc * dot(A.zAxis, B.xAxis)));

			mtvAxis = B.xAxis;

		}
	}

	// Box B y-axis
	if (abs(dot(T, B.yAxis)) > (B.e1_Hc
		+ abs(A.e2_Wc * dot(A.xAxis, B.yAxis))
		+ abs(A.e1_Hc * dot(A.yAxis, B.yAxis))
		+ abs(A.e0_Dc * dot(A.zAxis, B.yAxis))))
	{
		std::cout << "no intersection in b-y axis\n";
		return true;
	}
	else
	{
		if (mtvMag >  (B.e1_Hc
			+ abs(A.e2_Wc * dot(A.xAxis, B.yAxis))
			+ abs(A.e1_Hc * dot(A.yAxis, B.yAxis))
			+ abs(A.e0_Dc * dot(A.zAxis, B.yAxis))))
		{
			mtvMag = (B.e1_Hc
				+ abs(A.e2_Wc * dot(A.xAxis, B.yAxis))
				+ abs(A.e1_Hc * dot(A.yAxis, B.yAxis))
				+ abs(A.e0_Dc * dot(A.zAxis, B.yAxis)));

			mtvAxis = B.yAxis;

		}
	}

	// Box B z-axis
	if (abs(dot(T, B.zAxis)) > (B.e0_Dc
		+ abs(A.e2_Wc * dot(A.xAxis, B.zAxis))
		+ abs(A.e1_Hc * dot(A.yAxis, B.zAxis))
		+ abs(A.e0_Dc * dot(A.zAxis, B.zAxis))))
	{
		std::cout << "no intersection in b-x axis\n";
		return true;
	}
	else
	{
		if (mtvMag >  (B.e0_Dc
			+ abs(A.e2_Wc * dot(A.xAxis, B.zAxis))
			+ abs(A.e1_Hc * dot(A.yAxis, B.zAxis))
			+ abs(A.e0_Dc * dot(A.zAxis, B.zAxis))))
		{
			mtvMag = (B.e0_Dc
				+ abs(A.e2_Wc * dot(A.xAxis, B.zAxis))
				+ abs(A.e1_Hc * dot(A.yAxis, B.zAxis))
				+ abs(A.e0_Dc * dot(A.zAxis, B.zAxis)));

			mtvAxis = B.zAxis;

		}
	}

	// Ax-Bx
	if (abs(dot(T, A.zAxis)*dot(A.yAxis, B.xAxis)
		- dot(T, A.yAxis)*dot(A.zAxis, B.xAxis)) >
		abs(A.e1_Hc * dot(A.zAxis, B.xAxis))
		+ abs(A.e0_Dc * dot(A.yAxis, B.xAxis))
		+ abs(B.e1_Hc * dot(A.xAxis, B.zAxis))
		+ abs(B.e0_Dc * dot(A.xAxis, B.yAxis)))
	{
		std::cout << "no intersection in ax-bx axis\n";
		return true;
	}
	else
	{
		if (mtvMag >  abs(A.e1_Hc * dot(A.zAxis, B.xAxis))
			+ abs(A.e0_Dc * dot(A.yAxis, B.xAxis))
			+ abs(B.e1_Hc * dot(A.xAxis, B.zAxis))
			+ abs(B.e0_Dc * dot(A.xAxis, B.yAxis)))
		{
			mtvMag = abs(A.e1_Hc * dot(A.zAxis, B.xAxis))
				+ abs(A.e0_Dc * dot(A.yAxis, B.xAxis))
				+ abs(B.e1_Hc * dot(A.xAxis, B.zAxis))
				+ abs(B.e0_Dc * dot(A.xAxis, B.yAxis));

			mtvAxis = vec4(cross(vec3(A.xAxis), vec3(B.xAxis)), 0.0f);

		}
	}

	// Ax-By
	if (abs(dot(T, A.zAxis)*dot(A.yAxis, B.yAxis)
		- dot(T, A.yAxis)*dot(A.zAxis, B.yAxis)) >
		abs(A.e1_Hc * dot(A.zAxis, B.yAxis))
		+ abs(A.e0_Dc * dot(A.yAxis, B.yAxis))
		+ abs(B.e2_Wc * dot(A.xAxis, B.zAxis))
		+ abs(B.e0_Dc * dot(A.xAxis, B.xAxis)))
	{
		std::cout << "no intersection in ax-by axis\n";
		return true;
	}
	else
	{
		if (mtvMag > abs(A.e1_Hc * dot(A.zAxis, B.yAxis))
			+ abs(A.e0_Dc * dot(A.yAxis, B.yAxis))
			+ abs(B.e2_Wc * dot(A.xAxis, B.zAxis))
			+ abs(B.e0_Dc * dot(A.xAxis, B.xAxis)))
		{
			mtvMag = abs(A.e1_Hc * dot(A.zAxis, B.yAxis))
				+ abs(A.e0_Dc * dot(A.yAxis, B.yAxis))
				+ abs(B.e2_Wc * dot(A.xAxis, B.zAxis))
				+ abs(B.e0_Dc * dot(A.xAxis, B.xAxis));

			mtvAxis = vec4(cross(vec3(A.xAxis), vec3(B.yAxis)), 0.0f);

		}
	}

	// Ax-Bz
	if (abs(dot(T, A.zAxis)*dot(A.yAxis, B.zAxis)
		- dot(T, A.yAxis)*dot(A.zAxis, B.zAxis)) >
		abs(A.e1_Hc * dot(A.zAxis, B.zAxis))
		+ abs(A.e0_Dc * dot(A.yAxis, B.zAxis))
		+ abs(B.e2_Wc * dot(A.xAxis, B.yAxis))
		+ abs(B.e1_Hc * dot(A.xAxis, B.xAxis)))
	{
		std::cout << "no intersection in ax-bz axis\n";
		return true;
	}
	else
	{
		if (mtvMag > abs(A.e1_Hc * dot(A.zAxis, B.zAxis))
			+ abs(A.e0_Dc * dot(A.yAxis, B.zAxis))
			+ abs(B.e2_Wc * dot(A.xAxis, B.yAxis))
			+ abs(B.e1_Hc * dot(A.xAxis, B.xAxis)))
		{
			mtvMag = abs(A.e1_Hc * dot(A.zAxis, B.zAxis))
				+ abs(A.e0_Dc * dot(A.yAxis, B.zAxis))
				+ abs(B.e2_Wc * dot(A.xAxis, B.yAxis))
				+ abs(B.e1_Hc * dot(A.xAxis, B.xAxis));

			mtvAxis = vec4(cross(vec3(A.xAxis), vec3(B.zAxis)), 0.0f);

		}
	}

	// Ay-Bx
	if (abs(dot(T, A.xAxis)*dot(A.zAxis, B.xAxis)
		- dot(T, A.zAxis)*dot(A.xAxis, B.xAxis)) >
		abs(A.e2_Wc * dot(A.zAxis, B.xAxis))
		+ abs(A.e0_Dc * dot(A.xAxis, B.xAxis))
		+ abs(B.e1_Hc * dot(A.yAxis, B.zAxis))
		+ abs(B.e0_Dc * dot(A.yAxis, B.yAxis)))
	{
		std::cout << "no intersection in ay-bx axis\n";
		return true;
	}
	else
	{
		if (mtvMag > abs(A.e2_Wc * dot(A.zAxis, B.xAxis))
			+ abs(A.e0_Dc * dot(A.xAxis, B.xAxis))
			+ abs(B.e1_Hc * dot(A.yAxis, B.zAxis))
			+ abs(B.e0_Dc * dot(A.yAxis, B.yAxis)))
		{
			mtvMag = abs(A.e2_Wc * dot(A.zAxis, B.xAxis))
				+ abs(A.e0_Dc * dot(A.xAxis, B.xAxis))
				+ abs(B.e1_Hc * dot(A.yAxis, B.zAxis))
				+ abs(B.e0_Dc * dot(A.yAxis, B.yAxis));

			mtvAxis = vec4(cross(vec3(A.yAxis), vec3(B.xAxis)), 0.0f);

		}
	}

	// Ay-By
	if (abs(dot(T, A.xAxis)*dot(A.zAxis, B.yAxis)
		- dot(T, A.zAxis)*dot(A.xAxis, B.yAxis)) >
		abs(A.e2_Wc * dot(A.zAxis, B.yAxis))
		+ abs(A.e0_Dc * dot(A.xAxis, B.yAxis))
		+ abs(B.e2_Wc * dot(A.yAxis, B.zAxis))
		+ abs(B.e0_Dc * dot(A.yAxis, B.xAxis)))
	{
		std::cout << "no intersection in ay-by axis\n";
		return true;
	}
	else
	{
		if (mtvMag > abs(A.e2_Wc * dot(A.zAxis, B.yAxis))
			+ abs(A.e0_Dc * dot(A.xAxis, B.yAxis))
			+ abs(B.e2_Wc * dot(A.yAxis, B.zAxis))
			+ abs(B.e0_Dc * dot(A.yAxis, B.xAxis)))
		{
			mtvMag = abs(A.e2_Wc * dot(A.zAxis, B.yAxis))
				+ abs(A.e0_Dc * dot(A.xAxis, B.yAxis))
				+ abs(B.e2_Wc * dot(A.yAxis, B.zAxis))
				+ abs(B.e0_Dc * dot(A.yAxis, B.xAxis));

			mtvAxis = vec4(cross(vec3(A.yAxis), vec3(B.yAxis)), 0.0f);

		}
	}

	// Ay-Bz
	if (abs(dot(T, A.xAxis)*dot(A.zAxis, B.zAxis)
		- dot(T, A.zAxis)*dot(A.xAxis, B.zAxis)) >
		abs(A.e2_Wc * dot(A.zAxis, B.zAxis))
		+ abs(A.e0_Dc * dot(A.xAxis, B.zAxis))
		+ abs(B.e2_Wc * dot(A.yAxis, B.yAxis))
		+ abs(B.e1_Hc * dot(A.yAxis, B.xAxis)))
	{
		std::cout << "no intersection in ay-bz axis\n";
		return true;
	}
	else
	{
		if (mtvMag >abs(A.e2_Wc * dot(A.zAxis, B.zAxis))
			+ abs(A.e0_Dc * dot(A.xAxis, B.zAxis))
			+ abs(B.e2_Wc * dot(A.yAxis, B.yAxis))
			+ abs(B.e1_Hc * dot(A.yAxis, B.xAxis)))
		{
			mtvMag = abs(A.e2_Wc * dot(A.zAxis, B.zAxis))
				+ abs(A.e0_Dc * dot(A.xAxis, B.zAxis))
				+ abs(B.e2_Wc * dot(A.yAxis, B.yAxis))
				+ abs(B.e1_Hc * dot(A.yAxis, B.xAxis));

			mtvAxis = vec4(cross(vec3(A.yAxis), vec3(B.zAxis)), 0.0f);

		}
	}

	// Az-Bx
	if (abs(dot(T, A.yAxis)*dot(A.xAxis, B.xAxis)
		- dot(T, A.xAxis)*dot(A.yAxis, B.xAxis)) >
		abs(A.e2_Wc * dot(A.yAxis, B.xAxis))
		+ abs(A.e1_Hc * dot(A.xAxis, B.xAxis))
		+ abs(B.e1_Hc * dot(A.zAxis, B.zAxis))
		+ abs(B.e0_Dc * dot(A.zAxis, B.yAxis)))
	{
		std::cout << "no intersection in az-bx axis\n";
		return true;
	}
	else
	{
		if (mtvMag >abs(A.e2_Wc * dot(A.yAxis, B.xAxis))
			+ abs(A.e1_Hc * dot(A.xAxis, B.xAxis))
			+ abs(B.e1_Hc * dot(A.zAxis, B.zAxis))
			+ abs(B.e0_Dc * dot(A.zAxis, B.yAxis)))
		{
			mtvMag = abs(A.e2_Wc * dot(A.yAxis, B.xAxis))
				+ abs(A.e1_Hc * dot(A.xAxis, B.xAxis))
				+ abs(B.e1_Hc * dot(A.zAxis, B.zAxis))
				+ abs(B.e0_Dc * dot(A.zAxis, B.yAxis));

			mtvAxis = vec4(cross(vec3(A.zAxis), vec3(B.xAxis)), 0.0f);

		}
	}

	// Az-By
	if (abs(dot(T, A.yAxis)* dot(A.xAxis, B.yAxis)
		- dot(T, A.xAxis)* dot(A.yAxis, B.yAxis)) >
		abs(A.e2_Wc * dot(A.yAxis, B.yAxis))
		+ abs(A.e1_Hc * dot(A.xAxis, B.yAxis))
		+ abs(B.e2_Wc * dot(A.zAxis, B.zAxis))
		+ abs(B.e0_Dc * dot(A.zAxis, B.xAxis)))
	{
		//std::cout << "no intersection in az-by axis\n";
		return true;
	}
	else
	{
		if (mtvMag >abs(A.e2_Wc * dot(A.yAxis, B.yAxis))
			+ abs(A.e1_Hc * dot(A.xAxis, B.yAxis))
			+ abs(B.e2_Wc * dot(A.zAxis, B.zAxis))
			+ abs(B.e0_Dc * dot(A.zAxis, B.xAxis)))
		{
			mtvMag = abs(A.e2_Wc * dot(A.yAxis, B.yAxis))
				+ abs(A.e1_Hc * dot(A.xAxis, B.yAxis))
				+ abs(B.e2_Wc * dot(A.zAxis, B.zAxis))
				+ abs(B.e0_Dc * dot(A.zAxis, B.xAxis));

			mtvAxis = vec4(cross(vec3(A.zAxis), vec3(B.yAxis)), 0.0f);

		}
	}

	// Az-Bz
	if (abs(dot(T, A.yAxis)*dot(A.xAxis, B.zAxis)
		- dot(T, A.xAxis)*dot(A.yAxis, B.zAxis)) >
		abs(A.e2_Wc * dot(A.yAxis, B.zAxis))
		+ abs(A.e1_Hc * dot(A.xAxis, B.zAxis))
		+ abs(B.e2_Wc * dot(A.zAxis, B.yAxis))
		+ abs(B.e1_Hc * dot(A.zAxis, B.xAxis)))
	{
		std::cout << "no intersection in az-bz axis\n";
		return true;
	}
	else
	{
		if (mtvMag >abs(A.e2_Wc * dot(A.yAxis, B.zAxis))
			+ abs(A.e1_Hc * dot(A.xAxis, B.zAxis))
			+ abs(B.e2_Wc * dot(A.zAxis, B.yAxis))
			+ abs(B.e1_Hc * dot(A.zAxis, B.xAxis)))
		{
			mtvMag = abs(A.e2_Wc * dot(A.yAxis, B.zAxis))
				+ abs(A.e1_Hc * dot(A.xAxis, B.zAxis))
				+ abs(B.e2_Wc * dot(A.zAxis, B.yAxis))
				+ abs(B.e1_Hc * dot(A.zAxis, B.xAxis));

			mtvAxis = vec4(cross(vec3(A.zAxis), vec3(B.zAxis)), 0.0f);

		}
	}

	mtv = vec4(mtvAxis)*mtvMag;
	cout << "Max Translation Vector: " << "X: " << mtv.x << " Y: " << mtv.y << " Z: " << mtv.z << endl;
	return false;
}
