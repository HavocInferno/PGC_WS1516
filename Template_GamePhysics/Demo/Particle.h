#pragma once

#include <DirectXMath.h>
#include "point.h"

using namespace DirectX;

class Particle : public SpringPoint
{
	friend class Fluid;
	friend class FluidSimulation;
private:
	float density;
	float pressure;

public:

	Particle(void);
	Particle(XMFLOAT3 position, float mass);
	~Particle(void);
	XMFLOAT3 getPosition();
	void computeCollisionWithBox(float deltaTime, float sphereSize,XMVECTOR upper, XMVECTOR lower);
};

