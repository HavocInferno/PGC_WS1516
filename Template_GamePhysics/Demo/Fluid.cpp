#include "Fluid.h"
#include <iostream>

float Fluid::getKernelSize() {
	return kernelSize;
}

void Fluid::setKernelSize(float newsize)
{
	kernelSize = newsize;
}

std::vector<Particle*>& Fluid::getParticles() {
	return particles;
}

std::vector<Particle*>& Fluid::getNeighbourParticles(Particle& particle) {
	return particles;
}

Fluid::Fluid(XMFLOAT3 initialPostion, XMINT3 numParticles, int exp, float kernelSize, float positioningStep, float stiffness, float restDensity, float viscosity) : 
	numParticles(numParticles), exp(exp), kernelSize(kernelSize), positioningStep(positioningStep), stiffness(stiffness), restDensity(restDensity), viscosity(viscosity)
{
	//particles = new std::vector<Particle*>();
	
	XMFLOAT3 currParticlePos = initialPostion;
	//position particles in as a box
	for (int i = 0; i < numParticles.x; i++) {
		currParticlePos.x = initialPostion.x + i * positioningStep; //TODO: plus some rand factor!

		for (int j = 0; j < numParticles.y; j++) {
			currParticlePos.y = initialPostion.y + j * positioningStep;
		
			for (int k = 0; k < numParticles.z; k++) {
				currParticlePos.z = initialPostion.z + k * positioningStep;
				
				particles.push_back(new Particle(currParticlePos, .01f));
			}
		}
	
		/*Particle particle = Particle(currParticlePos, .01f);
		std::cout << particle.position.x << "\t" << particle.position.x << "\t" << particle.position.x << "\t" << std::endl;*/
	}
}

Fluid::~Fluid(void)
{
	//TODO: destruct the particles
	/*std::cout << "Fluid destructor's called" << std::endl;
	for (auto particle = particles.begin(); particle != particles.end(); particle++) {
		delete *particle._Ptr;
	}*/
}
