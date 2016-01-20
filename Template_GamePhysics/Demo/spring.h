//#pragma once
#ifndef Spring_HEADER
#define Spring_HEADER
#include "point.h"

#include <DirectXMath.h>
using namespace DirectX;



class Spring
{
public:

	float gs_stiffness;
	float gs_initialLength;
	float gs_currentLength;
	SpringPoint* gs_point1;
	SpringPoint* gs_point2;

	Spring();
	Spring::Spring(SpringPoint* point1, SpringPoint* point2);
	void initialize();
	void computeElasticForces();
	void computeElasticForcesTmp();

	void setPoint(int pointIndex, SpringPoint* point);

	void setStiffness(float newstiff);
	void setLength(float newlen);
	void setEquilibriumLength(float newlen);
	void computeCurrentLength();

	void printSpring();
};

#endif