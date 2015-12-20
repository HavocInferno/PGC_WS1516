#pragma once

#include <DirectXMath.h>

using namespace DirectX;

class Particle
{
	friend class Fluid;
	friend class FluidSimulation;
private:
	XMFLOAT3 position;
	float mass;
	float density;
	float pressure;
	XMFLOAT3 pressureForce;
	XMFLOAT3 acceleration;
	XMFLOAT3 velocity;

public:
	XMFLOAT3 getPosition();

	Particle(void);
	Particle(XMFLOAT3 position, float mass);
	~Particle(void);
};

