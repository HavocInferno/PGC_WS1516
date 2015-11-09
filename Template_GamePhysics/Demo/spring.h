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
	Point* gs_point1;
	Point* gs_point2;

	Spring();
	Spring::Spring(Point* point1, Point* point2);
	void initialize();
	void computeElasticForces();

	void setPoint(int pointIndex, Point* point);

	void setStiffness(float newstiff);
	void setLength(float newlen);
	void computeCurrentLength();

};

#endif