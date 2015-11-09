#include <DirectXMath.h>
using namespace DirectX;
#include "vectorOperations.h"
#include "point.h"

#define g -9.81f

XMFLOAT3 gp_position;
XMFLOAT3 gp_velocity;
XMFLOAT3 gp_force;
float gp_mass;
float gp_damping;
bool gp_isStatic;

Point::Point()
{
	initialize();
}

Point::Point(XMFLOAT3 position)
{
	initialize();
	gp_position = position;


}

void Point::initialize()
{
	gp_position =	XMFLOAT3(0,0,0);
	gp_velocity =	XMFLOAT3(0,0,0);
	gp_force	=	XMFLOAT3(0,0,0);
	gp_mass		=	10.0f;
	gp_damping	=	0.0f;
	gp_isStatic =	false;
}

void Point::setPosition(XMFLOAT3 newpos) {
	gp_position = newpos;
};
void Point::setVelocity(XMFLOAT3 newvel) {
	gp_velocity = newvel;
};
void Point::setForce(XMFLOAT3 newf) {
	gp_force = newf;
};

void Point::setMass(float newmass) {
	gp_mass = newmass;
};
void Point::setDamping(float newdamp) {
	gp_damping = newdamp;
};
void Point::setStatic(bool isStatic) {
	gp_isStatic = isStatic;
};
void Point::addForce(XMFLOAT3 newForce)
{
	gp_force = addVector(newForce,gp_force);
};
void Point::addGravity()
{
	gp_velocity = addVector(gp_velocity,XMFLOAT3(0,g,0));
};
void Point::addDamping()
{
	gp_velocity = multiplyVecor(gp_velocity, gp_damping);
	//TODO: Time.deltaTime
};
void Point::IntegratePosition()
{

};
void Point::IntegrateVelocity()
{

};
