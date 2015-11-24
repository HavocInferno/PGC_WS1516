#pragma once
#ifndef rb3d_HEADER
#define rb3d_HEADER

#include <DirectXMath.h>
using namespace DirectX;

#include "vectorOperations.h"
#include "MassPoint.h"
#include <list>

class rigidBody
{
public:
	float massInverse;
	XMFLOAT3 r_position;
	XMFLOAT3 r_velocity;
	XMMATRIX inertiaTensorInverse;
	XMFLOAT4 orientation;
	XMFLOAT3 angularVelocity;

	XMFLOAT3 forceAccumulator;
	XMFLOAT3 torqueAccumulator;

	XMMATRIX transform;

	std::list<MassPoint>* points;

	void preCompute();

	rigidBody(void);
	rigidBody(std::list<MassPoint>* points, XMFLOAT3 vel, XMFLOAT3 rotation);
	~rigidBody(void);
};

#endif