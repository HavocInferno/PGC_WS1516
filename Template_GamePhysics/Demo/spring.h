#ifndef Spring_HEADER
#define Spring_HEADER

#include <DirectXMath.h>
using namespace DirectX;

#include "point.h"

class Spring
{
public:
	Point* gs_point1;
	Point* gs_point2;
	float gs_stiffness;
	float gs_initialLength;
	float gs_currentLength;

	void setPoint(int pointIndex, Point* point);

	void setStiffness(float newstiff);
	void setLength(float newlen);
};

#endif