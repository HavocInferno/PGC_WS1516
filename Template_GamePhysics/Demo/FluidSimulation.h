#pragma once

#include "Fluid.h";

class FluidSimulation
{
private:
	inline float static kernel(float& d, XMFLOAT3& x, XMFLOAT3& xi);
	inline XMFLOAT3 static kernelGradient(float& d, XMFLOAT3& x, XMFLOAT3& xi);
public:
	static void integrateFluid(Fluid& fluid, float timeStep, float& gravity, XMVECTOR& lowerBoxBoundary, XMVECTOR& upperBoxBoundary, bool useGravity, bool useWalls, bool useDamping);
	//FluidSimulation();
	//~FluidSimulation(void);
};

