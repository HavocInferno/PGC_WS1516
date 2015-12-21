#include "FluidSimulation.h"
#include "vectorOperations.h"
#include <iostream>

float FluidSimulation::kernel(float& d, XMFLOAT3& x, XMFLOAT3& xi) {
	float q = vectorLength(subVector(x, xi)) / d;

	if (0 <= q < 1)	{
		return 3 * (2 / 3 - q * q + q * q * q / 2) / 2 * pow(d, 3) * XM_PI;
	} else if (1 <= q < 2) {
		return 1 * (pow((2 - q), 3)) / 4 * pow(d, 3) * XM_PI;
	} else if (q >= 2) {
		return 0.f;
	}
}

XMFLOAT3 FluidSimulation::kernelGradient(float& d, XMFLOAT3& x, XMFLOAT3& xi) {
	float distance = vectorLength(subVector(x, xi));
	float q = distance / d;
	XMFLOAT3 direction;
	float kernel;
	
	XMStoreFloat3(&direction, XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&x), XMLoadFloat3(&xi))));

	if (0 <= q < 1)	{
		kernel = 9 * ((q - 4/3) * q) / 4 * pow(d, 4) * XM_PI;
	} else if (1 <= q < 2) {
		kernel = 3 * pow(-(2- q), 2) / 4 * pow(d, 4) * XM_PI;
	} else if (q >= 2) {
		kernel = 0.f;
	}

	return multiplyVector(direction, kernel);
}

void FluidSimulation::integrateFluid(Fluid& fluid, float timeStep) {
	//for each particle
	std::vector<Particle>* particles = fluid.getParticles();

	for (auto p1 = particles->begin(); p1 != particles->end(); p1++) {
		//check the position
		//XMStoreFloat3(&p1->position, XMVectorClamp(XMLoadFloat3(&p1->position), XMLoadFloat3(&XMFLOAT3(-.5f, -.5f, -.5f)), XMLoadFloat3(&XMFLOAT3(-.5f, -.5f, -.5f)))); 

		//1 find density
		for (auto p2 = particles->begin(); p2 != particles->end(); p2++) {
			p1->density += p2->gp_mass * kernel(fluid.kernelSize, p1->gp_position, p2->gp_position);
		}
	
		//2 find pressure from density aka equasion of state
		p1->pressure = fluid.stiffness * (pow(p1->density / fluid.restDensity, fluid.exp) - 1);
	}

	//3 find f_pressure
	for (auto p1 = particles->begin(); p1 != particles->end(); p1++) {
		//1 find density
		for (auto p2 = particles->begin(); p2 != particles->end(); p2++) {
			p1->gp_force = addVector(p1->gp_force, multiplyVector(kernelGradient(fluid.kernelSize, p1->gp_position, p2->gp_position), (p1->pressure + p2->pressure) * p1->gp_mass / p1->density));
		}
		p1->gp_force = multiplyVector(p1->gp_force, -.5f);

		//4 find acceleration
		p1->gp_acceleration = multiplyVector(p1->gp_force, 1/p1->gp_mass);

		//5 integrate values
		p1->gp_position = addVector(p1->gp_position, multiplyVector(p1->gp_velocity, timeStep));
		p1->gp_velocity = addVector(p1->gp_velocity, multiplyVector(p1->gp_acceleration, timeStep));
	}
}

//FluidSimulation::FluidSimulation()
//{
//}
//
//
//FluidSimulation::~FluidSimulation(void)
//{
//}
