#include <DirectXMath.h>
using namespace DirectX;

#include "point.h"
#include "spring.h"

Point* gs_point1;
Point* gs_point2;
float gs_stiffness = 40.0f;
float gs_initialLength = 1.0f;
float gs_currentLength = 1.0f;

Spring::Spring()
{
	initialize();
}

Spring::Spring(Point* point1, Point* point2)
{
	initialize();
	gs_point1 = point1;
	gs_point2 = point2;
}

void Spring::initialize()
{
	gs_point1 = nullptr;
	gs_point2 = nullptr;
	gs_currentLength=1;
	gs_initialLength = 1;
	gs_stiffness = 40;
}

void Spring::setPoint(int pointIndex, Point* point) {
	switch(pointIndex) {
	case 1: gs_point1 = point;
		break;
	case 2: gs_point2 = point;
		break;
	default:
		break;
	}
}

void Spring::setStiffness(float newstiff) {
	gs_stiffness = newstiff;
};
void Spring::setLength(float newlen) {
	gs_currentLength = newlen;
};