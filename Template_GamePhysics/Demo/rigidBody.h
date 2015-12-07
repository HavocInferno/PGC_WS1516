#pragma once
#ifndef rb3d_HEADER
#define rb3d_HEADER

#include <DirectXMath.h>
using namespace DirectX;

#include "vectorOperations.h"
#include "MassPoint.h"
#include <vector>

class rigidBody
{
private:
	float massInverse;
	bool isStatic;
	XMFLOAT3 r_position;
	XMFLOAT3 r_velocity;
	XMMATRIX inertiaTensorInverse;
	XMFLOAT4 orientation;
	XMFLOAT3 angularVelocity;
	XMFLOAT3 angularMomentum;
	XMFLOAT4 rotationQuaternion;
	//for shaping to the right ratio
	XMFLOAT3 scale;

	XMFLOAT3 forceAccumulator;
	XMFLOAT3 torqueAccumulator;

	XMMATRIX transform;

	std::vector<MassPoint>* points;
public:
	void preCompute();
	void computeInverInertTensAndAngVel();
	void integrateValues(float timeStep);
	void addGravity(float timeStep, float gravity);

	XMFLOAT3 getScale();
	XMFLOAT3 getPosition();
	XMFLOAT3 getVelocity();
	XMFLOAT3 getAngularVelocity();
	XMFLOAT3 getAngularMomentum();
	XMFLOAT4 getRotationQuaternion();
	std::vector<MassPoint>* getMassPoints();
	float getMassInverse();
	XMMATRIX getInertiaTensorInverse();
	void setPosition(XMFLOAT3 newPos);
	void setLinearVelocity(XMFLOAT3 lV);
	void setAngularMomentum(XMFLOAT3 aM);
	void setStatic(bool val);

	rigidBody(void);
	rigidBody(std::vector<MassPoint>* points, XMFLOAT3 vel, XMFLOAT3 rotation, XMFLOAT3 scale);
	~rigidBody(void);
};

#endif