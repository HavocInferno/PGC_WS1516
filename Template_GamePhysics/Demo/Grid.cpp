#include "Grid.h"
#include <iostream>

XMVECTOR Grid::getCellIndicesForParticle(Particle& particle) {
	return XMVectorFloor((XMLoadFloat3(&particle.gp_position) - (*lowerBoxBoundary)) / spacing);
}

int Grid::getOneDimensionalIndex(XMVECTOR& indices) {
	return getOneDimensionalIndex(XMVectorGetX(indices), XMVectorGetY(indices), XMVectorGetZ(indices));
}

int Grid::getOneDimensionalIndex(int i, int j, int k) {
	return static_cast<int>(i * XMVectorGetX(numCells)  + j * XMVectorGetY(numCells) + k);
}

XMVECTOR Grid::getNumCells() {
	return numCells;
}

Grid::Grid(float spacing, int maxPerCell, Fluid& fluid, XMVECTOR& lowerBoxBoundary, XMVECTOR& upperBoxBoundary) :
	spacing(spacing), maxPerCell(maxPerCell), lowerBoxBoundary(&lowerBoxBoundary), upperBoxBoundary(&upperBoxBoundary)
{
	XMVECTOR boundaryLength = upperBoxBoundary - lowerBoxBoundary;

	//check for 0
	if (this->spacing <= 0.f) {
		this->spacing = 0.06f;
	}

	//num cells on X, Y, Z axes
	numCells = XMVectorCeiling(boundaryLength / this->spacing);
	int intNumCells = static_cast<int>(XMVectorGetX(numCells) * XMVectorGetY(numCells) * XMVectorGetZ(numCells));
	particles = new Particle*[ maxPerCell * intNumCells ];
	numInCell = new unsigned short[intNumCells];
	for (int i = 0; i < intNumCells; i++) {
		numInCell[i] = 0;
	}

	//fill grid with particles
	//TODO: check if faster with XMFLOATs
	XMVECTOR temp;
	int currCellIndex;
	//current number of particles in a given cell
	unsigned short currNumInCell;
	for (auto particle = fluid.particles.begin(); particle != fluid.particles.end(); particle++) {
		//locate the right cell
		temp = getCellIndicesForParticle(*particle._Ptr);
		currCellIndex = getOneDimensionalIndex(temp);
		std::cout << "initial currCellIndex: " << currCellIndex << std::endl;
		std::cout << "position: " << particle->gp_position.x << " " << particle->gp_position.y << " " << particle->gp_position.z << std::endl; 
		//plus one particle
		//TODO: control the number of cells with maxPerCell value
		currNumInCell = numInCell[currCellIndex]++;
		particles[currCellIndex * maxPerCell + currNumInCell] = particle._Ptr;
	}
	numInCell;
}


Grid::~Grid(void)
{
	delete [] particles;
	delete [] numInCell;
}
