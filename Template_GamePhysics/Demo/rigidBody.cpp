#include "rigidBody.h"
#include <DirectXMath.h>
using namespace DirectX;

#include "vectorOperations.h"

float massInverse;
XMFLOAT3 position;
XMFLOAT3 velocity;
XMMATRIX inertiaTensorInverse;
XMFLOAT4 orientation;
XMFLOAT3 angularVelocity;

XMFLOAT3 forceAccumulator;
XMFLOAT3 torqueAccumulator;

XMMATRIX transform;

rigidBody::rigidBody(void)
{
}


rigidBody::~rigidBody(void)
{
}
