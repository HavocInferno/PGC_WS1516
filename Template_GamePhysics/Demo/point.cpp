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
	gp_bouncyness = 0.75;
	gp_groundFriction = 0.1f;
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
	gp_force = addVector(gp_force,XMFLOAT3(0,gravity*gp_mass,0));
};
void SpringPoint::addDamping(float deltaTime)
{
	gp_velocity = addVector(gp_velocity,multiplyVector(gp_velocity, -gp_damping*deltaTime));
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
	else
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
	if(!gp_isStatic)
		gp_acceleration = multiplyVector(gp_force, 1/gp_mass);
	else 
		gp_acceleration = XMFLOAT3(0,0,0);
};
void SpringPoint::resetForces()
{
	gp_force = XMFLOAT3(0,0,0);
}
void SpringPoint::computeCollision(float deltaTime, float sphereSize)
{
	//Ground at y=-1;
	if(!gp_isStatic)
	{
		if(gp_position.y<-1+sphereSize)
		{
			gp_position.y = (-1+sphereSize)-(gp_position.y+1-sphereSize)*gp_bouncyness; //simulates a dampend bounce with constant velocity
			gp_velocity.y = -gp_velocity.y*gp_bouncyness;

			//apply friction, scaled on the frametime
			gp_velocity.x -= gp_velocity.x*deltaTime*(1-gp_groundFriction);
			gp_velocity.z -= gp_velocity.z*deltaTime*(1-gp_groundFriction);
		}
	}
}
void SpringPoint::computeCollisionWithWalls(float deltaTime, float sphereSize, float xWall, float zWall, float ceiling)
{
	if(!gp_isStatic)
	{
		//Ground at y=-1;
		bool collided = true;
		while(collided)
		{
			collided = false;

			//test floor collision
			if(gp_position.y<-1+sphereSize)
			{
				collided = true;
				gp_position.y = (-1+sphereSize)-(gp_position.y+1-sphereSize)*gp_bouncyness; //simulates a dampend bounce with constant velocity
				gp_velocity.y = -gp_velocity.y*gp_bouncyness;

				//apply friction, scaled on the frametime
				gp_velocity.x -= gp_velocity.x*deltaTime*(gp_groundFriction);
				gp_velocity.z -= gp_velocity.z*deltaTime*(gp_groundFriction);
			}
			//test negative x-wall collision
			if(gp_position.x<-xWall+sphereSize)
			{
				collided = true;
				gp_position.x = (-xWall+sphereSize)-(gp_position.x+xWall-sphereSize)*gp_bouncyness; //simulates a dampend bounce with constant velocity
				gp_velocity.x = -gp_velocity.x*gp_bouncyness;

				//apply friction, scaled on the frametime
				gp_velocity.y -= gp_velocity.y*deltaTime*(gp_groundFriction);
				gp_velocity.z -= gp_velocity.z*deltaTime*(gp_groundFriction);
			}
			//test negative z-wall collision
			if(gp_position.z<-zWall+sphereSize)
			{
				collided = true;
				gp_position.z = (-zWall+sphereSize)-(gp_position.z+zWall-sphereSize)*gp_bouncyness; //simulates a dampend bounce with constant velocity
				gp_velocity.z = -gp_velocity.z*gp_bouncyness;

				//apply friction, scaled on the frametime
				gp_velocity.y -= gp_velocity.y*deltaTime*(gp_groundFriction);
				gp_velocity.x -= gp_velocity.x*deltaTime*(gp_groundFriction);
			}

			//test ceiling collision
			if(gp_position.y>ceiling-sphereSize)
			{
				collided = true;
				gp_position.y = (ceiling-sphereSize)-(gp_position.y-(ceiling-sphereSize))*gp_bouncyness; //simulates a dampend bounce with constant velocity
				gp_velocity.y = -gp_velocity.y*gp_bouncyness;

				//apply friction, scaled on the frametime
				gp_velocity.x -= gp_velocity.x*deltaTime*(gp_groundFriction);
				gp_velocity.z -= gp_velocity.z*deltaTime*(gp_groundFriction);
			}
			//test positive x-wall collision
			if(gp_position.x>xWall-sphereSize)
			{
				collided = true;
				gp_position.x = (xWall-sphereSize)-(gp_position.x-(xWall-sphereSize))*gp_bouncyness; //simulates a dampend bounce with constant velocity
				gp_velocity.x = -gp_velocity.x*gp_bouncyness;

				//apply friction, scaled on the frametime
				gp_velocity.y -= gp_velocity.y*deltaTime*(gp_groundFriction);
				gp_velocity.z -= gp_velocity.z*deltaTime*(gp_groundFriction);
			}
			//test positive z-wall collision
			if(gp_position.z>zWall-sphereSize)
			{
				collided = true;
				gp_position.z = (zWall-sphereSize)-(gp_position.z-(zWall-sphereSize))*gp_bouncyness; //simulates a dampend bounce with constant velocity
				gp_velocity.z = -gp_velocity.z*gp_bouncyness;

				//apply friction, scaled on the frametime
				gp_velocity.y -= gp_velocity.y*deltaTime*(gp_groundFriction);
				gp_velocity.x -= gp_velocity.x*deltaTime*(gp_groundFriction);
			}
		}
	}
}

XMFLOAT3 SpringPoint::getVelocity()
{
	return gp_velocity;
};