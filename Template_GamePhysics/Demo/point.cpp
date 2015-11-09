#include <DirectXMath.h>
using namespace DirectX;
#include "vectorOperations.h"
#include "point.h"

#define g -9.81f

XMFLOAT3 gp_position;
XMFLOAT3 gp_velocity;
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
void SpringPoint::addGravity()
{
	gp_acceleration = addVector(gp_velocity,XMFLOAT3(0,g,0));
};
void SpringPoint::addDamping()
{
	gp_velocity = multiplyVector(gp_velocity, gp_damping);
	//TODO: Time.deltaTime
};
void SpringPoint::IntegratePosition(float deltaTime)
{
	setPosition(addVector(gp_position,multiplyVector(gp_velocity,deltaTime)));
};
void SpringPoint::IntegrateVelocity(float deltaTime)
{
	setVelocity(addVector(gp_velocity,multiplyVector(gp_acceleration,deltaTime)));
};
void SpringPoint::computeAcceleration()
{
	gp_acceleration = multiplyVector(gp_force, 1/gp_mass);
	//addGravity();
};
void SpringPoint::resetForces()
{
	gp_force = XMFLOAT3(0,0,0);
}
