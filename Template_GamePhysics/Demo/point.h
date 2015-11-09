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
	XMFLOAT3 gp_velocity;
	XMFLOAT3 gp_force;
	XMFLOAT3 gp_acceleration;
	float gp_mass;
	float gp_damping;
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
	void addGravity();
	void addDamping(float deltaTime);

	
	void SpringPoint::IntegrateVelocity(float deltaTime);
	void SpringPoint::IntegratePosition(float deltaTime);
	void SpringPoint::computeAcceleration();
	void SpringPoint::resetForces();
};

#endif