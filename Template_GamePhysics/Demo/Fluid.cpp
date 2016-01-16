#include "Fluid.h"
#include <iostream>
#include <ctime>
#include "vectorOperations.h"

float Fluid::getKernelSize() {
	return kernelSize;
}

void Fluid::setKernelSize(float newsize)
{
	kernelSize = newsize;
}

std::vector<Particle>& Fluid::getParticles() {
	return particles;
}

std::vector<Particle*> Fluid::getNeighbourParticles(Particle& particle) {
	std::vector<Particle*> neigbours;
	for (auto particle = particles.begin(); particle != particles.end(); particle++) {
		//std::cout << "particle: " << particle._Ptr << std::endl;
		neigbours.push_back(particle._Ptr);
		//std::cout << "neighbour: " << *(neigbours.end() - 1)._Ptr << std::endl;
	}
	//std::cout << "Fluid neighbours size: " << neigbours.size() << std::endl;
	return neigbours;
}

Fluid::Fluid(XMFLOAT3 initialPostion, XMINT3 numParticles, int exp, float kernelSize, float positioningStep, float stiffness, float restDensity, float viscosity, bool random) : 
	numParticles(numParticles), exp(exp), kernelSize(kernelSize), positioningStep(positioningStep), stiffness(stiffness), restDensity(restDensity), viscosity(viscosity)
{
	//particles = new std::vector<Particle*>();
	if(random)
		srand(time(0));
	XMFLOAT3 currRandOffset = XMFLOAT3(0,0,0);
	XMFLOAT3 currParticlePos = initialPostion;
	//position particles in as a box
	for (int i = 0; i < numParticles.x; i++) {
		currParticlePos.x = initialPostion.x + i * positioningStep; //TODO: plus some rand factor!

		for (int j = 0; j < numParticles.y; j++) {
			currParticlePos.y = initialPostion.y + j * positioningStep;
		
			for (int k = 0; k < numParticles.z; k++) {
				currParticlePos.z = initialPostion.z + k * positioningStep;
				if(random)
					currRandOffset = XMFLOAT3( (((float)rand()/(RAND_MAX))-.5f)*(kernelSize/50),(((float)rand()/(RAND_MAX))-.5f)*(kernelSize/50) ,(((float)rand()/(RAND_MAX))-.5f)*(kernelSize/50));
				particles.push_back(Particle(addVector(currParticlePos,currRandOffset), .01f));
				//std::cout << particles.end()._Ptr << std::endl;
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

void Fluid::recomputeGrid()
{
	return;
}
