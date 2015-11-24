#pragma once

#include <DirectXMath.h>
using namespace DirectX;

class MassPoint
{
public:
	XMFLOAT3 position;
	XMFLOAT3 velocity;
	float mass;

	MassPoint(void);
	MassPoint(XMFLOAT3 pos, float m, float v);
	~MassPoint(void);
};

