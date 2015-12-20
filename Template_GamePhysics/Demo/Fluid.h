#pragma once

#include <vector>
#include "Particle.h"
#include <DirectXMath.h>

using namespace DirectX;

class Fluid
{
	friend class FluidSimulation;
private:
	int exp;
	float kernelSize;
	float stiffness;
	float restDensity;
	float viscosity;

	//num of particles on X, Y and Z axes
	XMINT3 numParticles;
	
	
	std::vector<Particle>* particles;
public:
	float getKernelSize();
	std::vector<Particle>* getParticles();

	Fluid(XMFLOAT3 initialPostion, XMINT3 numParticles, int exp, float kernelSize, float stiffness, float restDensity, float viscosity);
	~Fluid(void);
};

