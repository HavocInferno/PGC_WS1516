#pragma once
#ifndef rb3d_HEADER
#define rb3d_HEADER

#include <DirectXMath.h>
using namespace DirectX;

#include "vectorOperations.h"

class rigidBody
{
public:
	float massInverse;
	XMFLOAT3 position;
	XMFLOAT3 velocity;
	XMMATRIX inertiaTensorInverse;
	XMFLOAT4 orientation;
	XMFLOAT3 angularVelocity;

	XMFLOAT3 forceAccumulator;
	XMFLOAT3 torqueAccumulator;

	XMMATRIX transform;

	rigidBody(void);
	~rigidBody(void);
};

#endif