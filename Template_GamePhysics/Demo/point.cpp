#include <DirectXMath.h>
using namespace DirectX;
#include "vectorOperations.h"
#include "point.h"

#define g -9.81f

XMFLOAT3 gp_position;
XMFLOAT3 gp_posTemp;
XMFLOAT3 gp_velocity;
XMFLOAT3 gp_velTemp;
XMFLOAT3 gp_acceleration;
XMFLOAT3 gp_force;
float gp_mass;
float gp_damping;
bool gp_isStatic;

SpringPoint::SpringPoint()
{
	initialize();
}

SpringPoint::SpringPoint(XMFLOAT3 position)
{
	initialize();
	gp_position = position;


}

void SpringPoint::initialize()
{
	gp_position =	XMFLOAT3(0,0,0);
	gp_velocity =	XMFLOAT3(0,0,0);
	gp_force	=	XMFLOAT3(0,0,0);
	gp_acceleration =	XMFLOAT3(0,0,0);
	gp_mass		=	10.0f;
	gp_damping	=	0.0f;
	gp_isStatic =	false;
}

void SpringPoint::setPosition(XMFLOAT3 newpos) {
	gp_position = newpos;
};
void SpringPoint::setVelocity(XMFLOAT3 newvel) {
	gp_velocity = newvel;
};
void SpringPoint::setForce(XMFLOAT3 newf) {
	gp_force = newf;
};

void SpringPoint::setMass(float newmass) {
	gp_mass = newmass;
};
void SpringPoint::setDamping(float newdamp) {
	gp_damping = newdamp;
};
void SpringPoint::setStatic(bool isStatic) {
	gp_isStatic = isStatic;
};
void SpringPoint::addForce(XMFLOAT3 newForce)
{
	gp_force = addVector(newForce,gp_force);
};
void SpringPoint::addGravity(float gravity)
{
	gp_force = addVector(gp_velocity,XMFLOAT3(0,gravity*gp_mass*0.001,0));
};
void SpringPoint::addDamping(float deltaTime)
{
	gp_velocity = addVector(gp_velocity,multiplyVector(gp_velocity, -gp_damping*deltaTime));
	//TODO: Time.deltaTime
};
void SpringPoint::IntegratePosition(float deltaTime)
{
	if(!gp_isStatic)
	setPosition(addVector(gp_position,multiplyVector(gp_velocity,deltaTime)));
};
void SpringPoint::IntegratePosition(float deltaTime, XMFLOAT3 vel)
{
	if(!gp_isStatic)
	setPosition(addVector(gp_position,multiplyVector(vel,deltaTime)));
};
XMFLOAT3 SpringPoint::IntegratePositionTmp(float deltaTime)
{
	if(!gp_isStatic)
	return addVector(gp_position,multiplyVector(gp_velocity,deltaTime));
	return gp_position;
};
void SpringPoint::IntegrateVelocity(float deltaTime)
{
	setVelocity(addVector(gp_velocity,multiplyVector(gp_acceleration,deltaTime)));
};
XMFLOAT3 SpringPoint::IntegrateVelocityTmp(float deltaTime)
{
	return addVector(gp_velocity,multiplyVector(gp_acceleration,deltaTime));
};
void SpringPoint::computeAcceleration()
{
	gp_acceleration = multiplyVector(gp_force, 1/gp_mass);
};
void SpringPoint::resetForces()
{
	gp_force = XMFLOAT3(0,0,0);
}
