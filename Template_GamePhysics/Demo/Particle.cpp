#include "Particle.h"


XMFLOAT3 Particle::getPosition() {
	return position;
}

Particle::Particle(void) {
}

Particle::Particle(XMFLOAT3 position, float mass) : 
	position(position), mass(mass), density(0.f), pressure(0.f), pressureForce(0.f, 0.f, 0.f), acceleration(0.f, 0.f, 0.f), velocity(0.f, 0.f, 0.f)
{
}


Particle::~Particle(void)
{
}
