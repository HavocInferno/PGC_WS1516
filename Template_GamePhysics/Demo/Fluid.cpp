#include "Fluid.h"
#include <iostream>

float Fluid::getKernelSize() {
	return kernelSize;
}

std::vector<Particle>* Fluid::getParticles() {
	return particles;
}

Fluid::Fluid(XMFLOAT3 initialPostion, XMINT3 numParticles, int exp, float kernelSize, float positioningStep, float stiffness, float restDensity, float viscosity) : 
	numParticles(numParticles), exp(exp), kernelSize(kernelSize), positioningStep(positioningStep), stiffness(stiffness), restDensity(restDensity), viscosity(viscosity)
{
	particles = new std::vector<Particle>();
	
	XMFLOAT3 currParticlePos = initialPostion;
	//position particles in as a box
	for (int i = 0; i < numParticles.x; i++) {
		currParticlePos.x = initialPostion.x + i * positioningStep; //TODO: plus some rand factor!

		for (int j = 0; j < numParticles.y; j++) {
			currParticlePos.y = initialPostion.y + j * positioningStep;
		
			for (int k = 0; k < numParticles.z; k++) {
				currParticlePos.z = initialPostion.z + k * positioningStep;
				
				particles->push_back(Particle(currParticlePos, .01f));
			}
		}
	
		/*Particle particle = Particle(currParticlePos, .01f);
		std::cout << particle.position.x << "\t" << particle.position.x << "\t" << particle.position.x << "\t" << std::endl;*/
	}
}

Fluid::~Fluid(void)
{
	//TODO: check if frees up the memory correctly
	delete(particles);
}
