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

	std::vector<Particle*> getNeighbourParticles(Particle& particle) { //TODO: Make this something useful
		std::vector<Particle*> neigbours;
		XMVECTOR particleIndices = grid->getCellIndicesForParticle(particle);
		int currCellIndex;
		int iParticleIndex = XMVectorGetX(particleIndices);
		int jParticleIndex = XMVectorGetY(particleIndices);
		int kParticleIndex = XMVectorGetZ(particleIndices);
		int counter = 0;
		for (int i = iParticleIndex - 1; i < iParticleIndex + 2; i++) {
			for (int j = jParticleIndex - 1; j < jParticleIndex + 2; j++) {
				for (int k = kParticleIndex - 1; k < kParticleIndex + 2; k++) {
					//go through all particles in a cell
					currCellIndex = grid->getOneDimensionalIndex(i, j, k);
					std::cout << "indices: " << i << " " << j << " " << " " << k << std::endl;
					std::cout << "currCellIndex: " << currCellIndex << std::endl;
					std::cout << "numInCell: " << grid->numInCell[currCellIndex] << std::endl;
					for (int c = 0; c < grid->numInCell[currCellIndex]; c++) {
						neigbours.push_back(grid->particles[currCellIndex + c]);
						counter++;
					}

				}
			}
		}
		std::cout << "counter: " << counter << std::endl;
		std::cout << "GridBasedFluid neighbours size: " << neigbours.size() << std::endl;
		return neigbours;
	}

	~GridBasedFluid(void) {
		std::cout << "GridBasedDestrcutor' called" << std::endl;
		delete grid;
	}
};