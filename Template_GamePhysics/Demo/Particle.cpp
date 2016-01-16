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
void Particle::computeCollisionWithBox(float deltaTime, float sphereSize,XMVECTOR upper, XMVECTOR lower)
{
	if(!gp_isStatic)
	{
		//Ground at y=-1;
		bool collided = true;
		while(collided)
		{
			collided = false;

			//test floor collision
			if(gp_position.y<XMVectorGetY(lower)+sphereSize)
			{
				collided = true;
				gp_position.y = (XMVectorGetY(lower)+sphereSize)-(gp_position.y-XMVectorGetY(lower)-sphereSize)*gp_bouncyness; //simulates a dampend bounce with constant velocity
				gp_velocity.y = -gp_velocity.y*gp_bouncyness;

				//apply friction, scaled on the frametime
				gp_velocity.x -= gp_velocity.x*deltaTime*(gp_groundFriction);
				gp_velocity.z -= gp_velocity.z*deltaTime*(gp_groundFriction);
			}
			//test negative x-wall collision
			if(gp_position.x<XMVectorGetX(lower)+sphereSize)
			{
				collided = true;
				gp_position.x = (XMVectorGetX(lower)+sphereSize)-(gp_position.x-XMVectorGetX(lower)-sphereSize)*gp_bouncyness; //simulates a dampend bounce with constant velocity
				gp_velocity.x = -gp_velocity.x*gp_bouncyness;

				//apply friction, scaled on the frametime
				gp_velocity.y -= gp_velocity.y*deltaTime*(gp_groundFriction);
				gp_velocity.z -= gp_velocity.z*deltaTime*(gp_groundFriction);
			}
			//test negative z-wall collision
			if(gp_position.z<XMVectorGetZ(lower)+sphereSize)
			{
				collided = true;
				gp_position.z = (XMVectorGetZ(lower)+sphereSize)-(gp_position.z-XMVectorGetZ(lower)-sphereSize)*gp_bouncyness; //simulates a dampend bounce with constant velocity
				gp_velocity.z = -gp_velocity.z*gp_bouncyness;

				//apply friction, scaled on the frametime
				gp_velocity.y -= gp_velocity.y*deltaTime*(gp_groundFriction);
				gp_velocity.x -= gp_velocity.x*deltaTime*(gp_groundFriction);
			}

			//test ceiling collision
			if(gp_position.y>XMVectorGetY(upper)-sphereSize)
			{
				collided = true;
				gp_position.y = (XMVectorGetY(upper)-sphereSize)-(gp_position.y-(XMVectorGetY(upper)-sphereSize))*gp_bouncyness; //simulates a dampend bounce with constant velocity
				gp_velocity.y = -gp_velocity.y*gp_bouncyness;

				//apply friction, scaled on the frametime
				gp_velocity.x -= gp_velocity.x*deltaTime*(gp_groundFriction);
				gp_velocity.z -= gp_velocity.z*deltaTime*(gp_groundFriction);
			}
			//test positive x-wall collision
			if(gp_position.x>XMVectorGetX(upper)-sphereSize)
			{
				collided = true;
				gp_position.x = (XMVectorGetX(upper)-sphereSize)-(gp_position.x-(XMVectorGetX(upper)-sphereSize))*gp_bouncyness; //simulates a dampend bounce with constant velocity
				gp_velocity.x = -gp_velocity.x*gp_bouncyness;

				//apply friction, scaled on the frametime
				gp_velocity.y -= gp_velocity.y*deltaTime*(gp_groundFriction);
				gp_velocity.z -= gp_velocity.z*deltaTime*(gp_groundFriction);
			}
			//test positive z-wall collision
			if(gp_position.z>XMVectorGetZ(upper)-sphereSize)
			{
				collided = true;
				gp_position.z = (XMVectorGetZ(upper)-sphereSize)-(gp_position.z-(XMVectorGetZ(upper)-sphereSize))*gp_bouncyness; //simulates a dampend bounce with constant velocity
				gp_velocity.z = -gp_velocity.z*gp_bouncyness;

				//apply friction, scaled on the frametime
				gp_velocity.y -= gp_velocity.y*deltaTime*(gp_groundFriction);
				gp_velocity.x -= gp_velocity.x*deltaTime*(gp_groundFriction);
			}
		}
	}
}
