#include "MassPoint.h"

#include <DirectXMath.h>
using namespace DirectX;

XMFLOAT3 position;
XMFLOAT3 worldPosition;
XMFLOAT3 velocity;
float mass;

MassPoint::MassPoint(void)
{
}

MassPoint::MassPoint(XMFLOAT3 pos, float m, float v, XMFLOAT3 force)
{
	position = worldPosition = pos;
	mass = m;
	this->force = force;
	velocity = XMFLOAT3(0.f, 0.f, 0.f);

}

MassPoint::~MassPoint(void)
{
}
