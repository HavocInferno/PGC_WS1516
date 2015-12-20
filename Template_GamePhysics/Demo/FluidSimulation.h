#pragma once

#include "Fluid.h";

class FluidSimulation
{
private:
	inline float static kernel(float& d, XMFLOAT3& x, XMFLOAT3& xi);
	inline XMFLOAT3 static kernelGradient(float& d, XMFLOAT3& x, XMFLOAT3& xi);
	inline float static equasionOfState(float& stiffness, float& exp);
public:
	static void integrateFluid(Fluid& fluid, float timeStep);

	//FluidSimulation();
	//~FluidSimulation(void);
};

