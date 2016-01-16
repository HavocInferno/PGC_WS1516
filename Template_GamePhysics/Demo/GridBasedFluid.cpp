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

	void recomputeGrid()
	{
		grid->recompute(*this);
	}

	std::vector<Particle*> getNeighbourParticles(Particle& particle) { //TODO: Make this something useful
		std::vector<Particle*> neigbours;
		XMVECTOR particleIndices = grid->getCellIndicesForParticle(particle);
		int currCellIndex;
		int iParticleIndex = XMVectorGetX(particleIndices);
		int jParticleIndex = XMVectorGetY(particleIndices);
		int kParticleIndex = XMVectorGetZ(particleIndices);
		int iStart = iParticleIndex < 1 ? 0 : (iParticleIndex - 1);
		int jStart = jParticleIndex < 1 ? 0 : (jParticleIndex - 1);
		int kStart = kParticleIndex < 1 ? 0 : (kParticleIndex - 1);
		int iEnd = iParticleIndex < (XMVectorGetX(grid->numCells) - 1) ? (iParticleIndex + 1) : (XMVectorGetX(grid->numCells) - 1);
		int jEnd = jParticleIndex < (XMVectorGetY(grid->numCells) - 1) ? (jParticleIndex + 1) : (XMVectorGetY(grid->numCells) - 1);
		int kEnd = kParticleIndex < (XMVectorGetZ(grid->numCells) - 1) ? (kParticleIndex + 1) : (XMVectorGetZ(grid->numCells) - 1);
		//int counter = 0;
		for (int i = iStart; i <= iEnd; i++) {
			for (int j = jStart; j <= jEnd; j++) {
				for (int k = kStart; k <= kEnd; k++) {
					//go through all particles in a cell
					currCellIndex = grid->getOneDimensionalIndex(i, j, k);
					//std::cout << "indices: " << i << " " << j << " " << " " << k << std::endl;
					//std::cout << "currCellIndex: " << currCellIndex << std::endl;
					//std::cout << "numInCell: " << grid->numInCell[currCellIndex] << std::endl;
					for (int c = 0; c < grid->numInCell[currCellIndex]; c++) {
						//std::cout << "grid particle: " << &grid->particles[currCellIndex + c] << std::endl;
						neigbours.push_back(grid->particles[currCellIndex * grid->maxPerCell + c]);
						//counter++;
					}
					//std::cout << "wtf" << std::endl;

				}
			}
		}
		/*std::cout << "counter: " << counter << std::endl;
		std::cout << "GridBasedFluid neighbours size: " << neigbours.size() << std::endl;*/
		return neigbours;
	}

	~GridBasedFluid(void) {
		std::cout << "GridBasedDestrcutor' called" << std::endl;
		delete grid;
	}
};