#include <DirectXMath.h>
#include "spring.h"
using namespace DirectX;

#include "point.h"
#include <iostream>


SpringPoint* gs_point1;
SpringPoint* gs_point2;
float gs_stiffness = 40.0f;
float gs_initialLength = 1.0f;
float gs_currentLength = 1.0f;
float gs_currentLengthTmp = 1.0f;
float damping = 0.5f;

Spring::Spring()
{
	initialize();
};

Spring::Spring(SpringPoint* point1, SpringPoint* point2)
{
	initialize();
	gs_point1 = point1;
	gs_point2 = point2;
};

void Spring::initialize()
{
	gs_point1 = nullptr;
	gs_point2 = nullptr;
	gs_currentLength=1;
	gs_initialLength = 1;
	gs_stiffness = 40;
};

void Spring::setPoint(int pointIndex, SpringPoint* point) {
	switch(pointIndex) {
	case 1: gs_point1 = point;
		break;
	case 2: gs_point2 = point;
		break;
	default:
		break;
	};
};

void Spring::setStiffness(float newstiff) {
	gs_stiffness = newstiff;
};
void Spring::setLength(float newlen) {
	gs_currentLength = newlen;
};
void Spring::setRestLength(float newlen){
	gs_initialLength = newlen;
}
void Spring::computeCurrentLength()
{
	gs_currentLength = vectorLength(subVector(gs_point1->gp_position,gs_point2->gp_position));
};
void Spring::computeCurrentLengthTmp()
{
	gs_currentLengthTmp = vectorLength(subVector(gs_point1->gp_posTemp,gs_point2->gp_posTemp));
};
void Spring::computeElasticForces()
{
	//-k(l-L)(xi-xj)/l
	computeCurrentLength();
	gs_point1->addForce(multiplyVector(subVector(gs_point1->gp_position,gs_point2->gp_position),-(gs_stiffness*(gs_currentLength-gs_initialLength))/gs_currentLength));
	gs_point2->addForce(multiplyVector(subVector(gs_point2->gp_position,gs_point1->gp_position),-(gs_stiffness*(gs_currentLength-gs_initialLength))/gs_currentLength));
};
void Spring::computeElasticForcesTmp()
{
	//-k(l-L)(xi-xj)/l
	computeCurrentLengthTmp();
	gs_point1->addForce(multiplyVector(subVector(gs_point1->gp_posTemp,gs_point2->gp_posTemp),-(gs_stiffness*(gs_currentLengthTmp-gs_initialLength))/gs_currentLengthTmp));
	gs_point2->addForce(multiplyVector(subVector(gs_point2->gp_posTemp,gs_point1->gp_posTemp),-(gs_stiffness*(gs_currentLengthTmp-gs_initialLength))/gs_currentLengthTmp));
};
void Spring::computeDampingForces()
{
	//-c*v
	// in vector notation: c*dotProduct(v,(xi-xj)/l).... i think........
	// c = damping
	// v1 = dotProduct(gs_point1->getVelocity(),
	// v2 = gs_point2->getVelocity()
	// (xi-xj) = subVector(gs_point1->gp_position,gs_point2->gp_position)
	// (xj-xi) = subVector(gs_point2->gp_position,gs_point1->gp_position)
	// l = gs_currentLength
	computeCurrentLength();
	//We only want the damping to occur in the direction of the spring!
	// get 1d force
	XMFLOAT3 e = multiplyVector(subVector(gs_point2->gp_position,gs_point1->gp_position),1/gs_currentLength);
	float v1 = dotProduct(e,gs_point1->gp_velocity);
	float v2 = dotProduct(e,gs_point2->gp_velocity);
	//map it back to 3d
	XMFLOAT3 fd = multiplyVector(e,-damping*(v1-v2));
	gs_point1->addForce(fd);
	gs_point2->addForce(multiplyVector(fd,-1));
};
void Spring::computeDampingForcesTmp()
{
	//-c*v
	// in vector notation: c*dotProduct(v,(xi-xj)/l).... i think........
	// c = damping
	// v1 = dotProduct(gs_point1->getVelocity(),
	// v2 = gs_point2->getVelocity()
	// (xi-xj) = subVector(gs_point1->gp_position,gs_point2->gp_position)
	// (xj-xi) = subVector(gs_point2->gp_position,gs_point1->gp_position)
	// l = gs_currentLength
	computeCurrentLengthTmp();
	//We only want the damping to occur in the direction of the spring!
	// get 1d force
	XMFLOAT3 e = multiplyVector(subVector(gs_point1->gp_posTemp,gs_point2->gp_posTemp),1/gs_currentLengthTmp);
	float v1 = dotProduct(e,gs_point1->gp_velTemp);
	float v2 = dotProduct(e,gs_point2->gp_velTemp);
	//map it back to 3d
	XMFLOAT3 fd = multiplyVector(e,-damping*(v1-v2));
	gs_point1->addForce(fd);
	gs_point2->addForce(multiplyVector(fd,-1));
};

void Spring::setDamping(float d) 
{
	damping = d;
};

void Spring::printSpring()
{
	std::cout << "spring info: [stiffness=" << gs_stiffness << ", length=" << gs_currentLength << " (initial=" << gs_initialLength << ")]\n";
	std::cout << "point1: [x=" << gs_point1->gp_position.x << ", y=" << gs_point1->gp_position.y << ", z=" << gs_point1->gp_position.z << "]\n";
	std::cout << "point2: [x=" << gs_point2->gp_position.x << ", y=" << gs_point2->gp_position.y << ", z=" << gs_point2->gp_position.z << "]\n";
};

float Spring::getCurrentLength() 
{
	return gs_currentLength;
}
