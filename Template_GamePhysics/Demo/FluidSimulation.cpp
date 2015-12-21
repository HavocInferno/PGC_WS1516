#include "FluidSimulation.h"
#include "vectorOperations.h"
#include <iostream>

float FluidSimulation::kernel(float& d, XMFLOAT3& x, XMFLOAT3& xi) {
	float q = XMVectorGetX(XMVector3Length(XMVectorSubtract(XMLoadFloat3(&x), XMLoadFloat3(&xi)))) / d;
	
	if (0.f <= q && q < 1.f)	{
		return 3 * (2.f / 3 - q * q + .5f * pow(q, 3.f) ) / 2 * pow(d, 3) * XM_PI;
	} else if (1.f <= q && q < 2.f) {
		return (pow((2 - q), 3)) / 4 * pow(d, 3.f) * XM_PI;
	} else if (q >= 2.f) {
		return 0.f;
	}
}

XMFLOAT3 FluidSimulation::kernelGradient(float& d, XMFLOAT3& x, XMFLOAT3& xi) {
	float q = XMVectorGetX(XMVector3Length(XMVectorSubtract(XMLoadFloat3(&x), XMLoadFloat3(&xi)))) / d;
	XMFLOAT3 direction;
	float kernel;
	
	XMStoreFloat3(&direction, XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&x), XMLoadFloat3(&xi))));

	if (0.f <= q && q < 1.f)	{
		kernel = 9 * ((q - 4.f /3) * q) / 4 * pow(d, 4) * XM_PI;
	} else if (1.f <= q && q < 2.f) {
		kernel = -3 * pow((2- q), 2) / 4 * pow(d, 4) * XM_PI;
	} else if (q >= 2.f) {
		kernel = 0.f;
	}

	return multiplyVector(direction, kernel);
}

void FluidSimulation::integrateFluid(Fluid& fluid, float timeStep) {
	//for each particle
	std::vector<Particle>* particles = fluid.getParticles();

	//DEBUG
	for (auto p1 = particles->begin(); p1 != particles->end(); p1++) {
		std::cout << "position: " << p1->position.x << "\t" << p1->position.y << "\t" << p1->position.z << "\t" <<  std::endl;
		std::cout << "mass: " << p1->mass << std::endl;
		std::cout << "density: " << p1->density << std::endl;
		std::cout << "pressure: " << p1->pressure << std::endl;
		std::cout << "pressureForce: " << p1->pressureForce.x << "\t" << p1->pressureForce.y << "\t" << p1->pressureForce.z << "\t" <<  std::endl;
		std::cout << "velocity: " << p1->velocity.x << "\t" << p1->velocity.y << "\t" << p1->velocity.z << "\t" <<  std::endl;
		std::cout << "acceleration: " << p1->acceleration.x << "\t" << p1->acceleration.y << "\t" << p1->acceleration.z << "\t" <<  std::endl << std::endl;
	}

	for (auto p1 = particles->begin(); p1 != particles->end(); p1++) {
		//check the position
		//XMStoreFloat3(&p1->position, XMVectorClamp(XMLoadFloat3(&p1->position), XMLoadFloat3(&XMFLOAT3(-.5f, -.5f, -.5f)), XMLoadFloat3(&XMFLOAT3(-.5f, -.5f, -.5f)))); 

		//1 find density
		for (auto p2 = particles->begin(); p2 != particles->end(); p2++) {
			p1->density += p2->mass * kernel(fluid.kernelSize, p1->position, p2->position);
		}
	
		//2 find pressure from density aka equasion of state
		p1->pressure = fluid.stiffness * (pow(p1->density / fluid.restDensity, fluid.exp) - 1);
	}

	//3 find f_pressure
	for (auto p1 = particles->begin(); p1 != particles->end(); p1++) {
		//1 find density
		for (auto p2 = particles->begin(); p2 != particles->end(); p2++) {
			p1->pressureForce = addVector(p1->pressureForce, multiplyVector(kernelGradient(fluid.kernelSize, p1->position, p2->position), (p1->pressure + p2->pressure) * p1->mass / p1->density));
		}
		p1->pressureForce = multiplyVector(p1->pressureForce, -.5f);

		//4 find acceleration
		p1->acceleration = multiplyVector(p1->pressureForce, 1/p1->mass);

		//5 integrate values
		p1->position = addVector(p1->position, multiplyVector(p1->velocity, timeStep));
		p1->velocity = addVector(p1->velocity, multiplyVector(p1->acceleration, timeStep));
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
