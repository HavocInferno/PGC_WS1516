#include "Particle.h"

Particle::Particle(void) 
{
	initialize();
}

Particle::Particle(XMFLOAT3 position, float mass) 
{
	initialize();
	gp_position = position;
	gp_mass = mass;
}


Particle::~Particle(void)
{
}

XMFLOAT3 Particle::getPosition()
{
	return gp_position;
}
