#pragma once

#include <DirectXMath.h>
using namespace DirectX;

class MassPoint
{
public:
	XMFLOAT3 position;
	XMFLOAT3 worldPosition;
	XMFLOAT3 velocity;
	float mass;
	XMFLOAT3 force;

	MassPoint(void);
	MassPoint(XMFLOAT3 pos, float m, float v, XMFLOAT3 force);
	~MassPoint(void);
};

