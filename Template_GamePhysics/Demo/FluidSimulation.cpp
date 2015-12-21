#include "FluidSimulation.h"
#include "vectorOperations.h"
#include <iostream>

float FluidSimulation::kernel(float& d, XMFLOAT3& x, XMFLOAT3& xi) {
	float q = XMVectorGetX(XMVector3Length(XMVectorSubtract(XMLoadFloat3(&x), XMLoadFloat3(&xi)))) / d;
	float temp;
	
	if (0.f <= q && q < 1.f)	{
		return (3 * (2.f / 3 - q * q + .5f * pow(q, 3.f))) / (2 * pow(d, 3) * XM_PI);
	} else if (1.f <= q && q < 2.f) {
		return pow((2 - q), 3) / (4 * pow(d, 3.f) * XM_PI);
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
		kernel = (9 * ((q - 4.f /3) * q)) / (4 * pow(d, 3) * XM_PI);
	} else if (1.f <= q && q < 2.f) {
		kernel = (-3 * pow((2- q), 2)) / (4 * pow(d, 3) * XM_PI);
	} else if (q >= 2.f) {
		kernel = 0.f;
	}

	return multiplyVector(direction, kernel);
}

void FluidSimulation::integrateFluid(Fluid& fluid, float timeStep) {
	//for each particle
	std::vector<Particle>* particles = fluid.getParticles();

	//DEBUG
	/*for (auto p1 = particles->begin(); p1 != particles->end(); p1++) {
		std::cout << "position: " << p1->gp_position.x << "\t" << p1->gp_position.y << "\t" << p1->gp_position.z << "\t" <<  std::endl;
		std::cout << "mass: " << p1->gp_mass << std::endl;
		std::cout << "density: " << p1->density << std::endl;
		std::cout << "pressure: " << p1->pressure << std::endl;
		std::cout << "pressureForce: " << p1->gp_force.x << "\t" << p1->gp_force.y << "\t" << p1->gp_force.z << "\t" <<  std::endl;
		std::cout << "velocity: " << p1->gp_velocity.x << "\t" << p1->gp_velocity.y << "\t" << p1->gp_velocity.z << "\t" <<  std::endl;
		std::cout << "acceleration: " << p1->gp_acceleration.x << "\t" << p1->gp_acceleration.y << "\t" << p1->gp_acceleration.z << "\t" <<  std::endl << std::endl;
	}*/

	for (auto p1 = particles->begin(); p1 != particles->end(); p1++) {
		//check the position
		//XMStoreFloat3(&p1->position, XMVectorClamp(XMLoadFloat3(&p1->position), XMLoadFloat3(&XMFLOAT3(-.5f, -.5f, -.5f)), XMLoadFloat3(&XMFLOAT3(.5f, .5f, -5f)))); 

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
			p1->gp_force = addVector(p1->gp_force, 
				multiplyVector(kernelGradient(fluid.kernelSize, p1->gp_position, p2->gp_position), 
					(p1->pressure / pow(p1->density, 2.f) + p2->pressure / pow(p2->density, 2.f)) * p2->gp_mass));
		}
		p1->gp_force = multiplyVector(p1->gp_force, -p1->gp_mass);

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
