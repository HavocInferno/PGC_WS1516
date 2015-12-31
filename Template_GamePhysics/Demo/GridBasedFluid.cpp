#pragma once
#include "Fluid.h"
#include "Grid.h"
#include <iostream>

class GridBasedFluid : public Fluid {
	Grid* grid;

public:
	GridBasedFluid(XMFLOAT3 initialPostion, XMINT3 numParticles, int exp, float kernelSize, float positioningStep, float stiffness, float restDensity, float viscosity, XMVECTOR& lowerBoxBoundary, XMVECTOR& upperBoxBoundary) :
		Fluid(initialPostion, numParticles, exp, kernelSize, positioningStep, stiffness, restDensity, viscosity)
	{
		grid = new Grid(.06f, 10, *this, lowerBoxBoundary, upperBoxBoundary);
	}

	std::vector<Particle*>& getNeighbourParticles(Particle& particle) {
		return particles;
	}

	~GridBasedFluid(void) {
		std::cout << "GridBasedDestrcutor' called" << std::endl;
		delete grid;
	}
};