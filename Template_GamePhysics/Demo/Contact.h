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
	XMFLOAT3 c_normal;
	float depth;
	rigidBody body1, body2;

	Contact(void);
	~Contact(void);
};

#endif