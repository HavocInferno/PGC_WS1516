#pragma once
#ifndef contact_HEADER
#define contact_HEADER

#include <DirectXMath.h>
using namespace DirectX;

#include "vectorOperations.h"
#include "rigidBody.h"

class Contact
{
public:
	XMFLOAT3 c_position;
	XMVECTOR c_normal;
	XMFLOAT3 v_relative;
	float v_relative_dot;
	float depth;
	float impulse;
	rigidBody* body1,* body2;
	

	void calcRelativeVelocity();
	void calculateImpulse();

	Contact(XMFLOAT3 pos, XMVECTOR norm, rigidBody* rb1, rigidBody* rb2);
	Contact(void);
	~Contact(void);
};

#endif