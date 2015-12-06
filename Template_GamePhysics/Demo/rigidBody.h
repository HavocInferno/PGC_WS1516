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

	XMFLOAT3 getScale();
	XMFLOAT3 getPosition();
	XMFLOAT4 getRotationQuaternion();
	std::vector<MassPoint>* getMassPoints();

	rigidBody(void);
	rigidBody(std::vector<MassPoint>* points, XMFLOAT3 vel, XMFLOAT3 rotation, XMFLOAT3 scale);
	~rigidBody(void);
};

#endif