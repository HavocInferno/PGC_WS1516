#pragma once
#ifndef Point_HEADER
#define Point_HEADER

#include <DirectXMath.h>
using namespace DirectX;

#include "vectorOperations.h"


class SpringPoint
{
public:
	XMFLOAT3 gp_position;
	XMFLOAT3 gp_posTemp;
	XMFLOAT3 gp_velocity;
	XMFLOAT3 gp_velTemp;
	XMFLOAT3 gp_force;
	XMFLOAT3 gp_acceleration;
	float gp_mass;
	float gp_damping;
	float gp_groundFriction;
	float gp_bouncyness;
	bool gp_isStatic;

	void initialize();
	SpringPoint();
	SpringPoint(XMFLOAT3 position);

	void setPosition(XMFLOAT3 newpos);
	void setVelocity(XMFLOAT3 newvel);
	void setForce(XMFLOAT3 newf);

	void setMass(float newmass);
	void setDamping(float newdamp);
	void setStatic(bool isStatic);
	void addForce(XMFLOAT3 newForce);
	void addGravity(float gravity);
	void addDamping(float deltaTime);
	XMFLOAT3 getVelocity();

	void SpringPoint::IntegrateVelocity(float deltaTime);
	XMFLOAT3 SpringPoint::IntegrateVelocityTmp(float deltaTime);
	void SpringPoint::IntegratePosition(float deltaTime);
	void SpringPoint::IntegratePosition(float deltaTime, XMFLOAT3 vel);
	XMFLOAT3 SpringPoint::IntegratePositionTmp(float deltaTime);
	void SpringPoint::computeAcceleration();
	void SpringPoint::resetForces();
	void SpringPoint::computeCollision(float deltaTime, float sphereSize);
	void SpringPoint::computeCollisionWithWalls(float deltaTime, float sphereSize, float xWall, float zWall, float ceiling);
};

#endif