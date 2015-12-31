#pragma once
#include "Particle.h"
#include "Fluid.h"

class Grid
{
private:
	float spacing;
	int maxPerCell;
	Particle** particles;
	//array containing number of particles per cell
	unsigned short* numInCell;
	XMVECTOR* lowerBoxBoundary;
	XMVECTOR* upperBoxBoundary;

public:
	inline XMVECTOR getCellIndicesForParticle(Particle& particle);

	Grid(float spacing, int maxPerCell, Fluid& fluid, XMVECTOR& lowerBoxBoundary, XMVECTOR& upperBoxBoundary);
	~Grid(void);
};

