#ifndef Point_HEADER
#define Point_HEADER

#include <DirectXMath.h>
#include "vectorOperations.h"
using namespace DirectX;

class Point
{
public:
	XMFLOAT3 gp_position;
	XMFLOAT3 gp_velocity;
	XMFLOAT3 gp_force;
	float gp_mass;
	float gp_damping;
	bool gp_isStatic;

	void initialize();
	Point();
	Point(XMFLOAT3 position);

	void setPosition(XMFLOAT3 newpos);
	void setVelocity(XMFLOAT3 newvel);
	void setForce(XMFLOAT3 newf);

	void setMass(float newmass);
	void setDamping(float newdamp);
	void setStatic(bool isStatic);
	void addForce(XMFLOAT3 newForce);
	void addGravity();
	void addDamping();

	enum IntegrationMethod{IN_EULER, IN_MIDPOINT, IN_LEAPFROG};
	void Point::IntegrateVelocity();
	void Point::IntegratePosition();
};

#endif