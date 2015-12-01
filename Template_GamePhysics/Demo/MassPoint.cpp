#include "MassPoint.h"

#include <DirectXMath.h>
using namespace DirectX;

XMFLOAT3 position;
XMFLOAT3 velocity;
float mass;

MassPoint::MassPoint(void)
{
}

MassPoint::MassPoint(XMFLOAT3 pos, float m, float v, XMFLOAT3 force)
{
	position = pos;
	mass = m;
	this->force = force;
}

MassPoint::~MassPoint(void)
{
}
