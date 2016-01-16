#pragma once
#include "Particle.h"
#include "Fluid.h"

class Grid
{
	friend class GridBasedFluid;
private:
	float spacing;
	int maxPerCell;
	Particle** particles;
	//array containing number of particles per cell
	unsigned short* numInCell;
	XMVECTOR* lowerBoxBoundary;
	XMVECTOR* upperBoxBoundary;
	//num cells on X, Y, Z axes
	XMVECTOR numCells;

public:
	inline XMVECTOR getCellIndicesForParticle(Particle& particle);
	inline int getOneDimensionalIndex(XMVECTOR& indices);
	inline int getOneDimensionalIndex(int i, int j, int k);
	XMVECTOR getNumCells();
	void recompute(Fluid& fluid);


	Grid(float spacing, int maxPerCell, Fluid& fluid, XMVECTOR& lowerBoxBoundary, XMVECTOR& upperBoxBoundary);
	~Grid(void);
};

