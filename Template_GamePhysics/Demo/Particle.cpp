#include "Particle.h"

Particle::Particle(void) 
{
	initialize();
}

Particle::Particle(XMFLOAT3 position, float mass) : density(0.f), pressure(0.f)
{
	initialize();
	gp_position = position;
	gp_mass = mass;
	gp_bouncyness = 0.1;
}


Particle::~Particle(void)
{
}

XMFLOAT3 Particle::getPosition()
{
	return gp_position;
}
