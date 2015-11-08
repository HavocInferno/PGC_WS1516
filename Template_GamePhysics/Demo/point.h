#ifndef Point_HEADER
#define Point_HEADER

#include <DirectXMath.h>
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
};

#endif