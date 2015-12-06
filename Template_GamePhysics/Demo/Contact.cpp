#include "Contact.h"
#include <DirectXMath.h>
using namespace DirectX;

#include "vectorOperations.h"
#include "rigidBody.h"

XMFLOAT3 c_position;
XMVECTOR c_normal;
float depth;
rigidBody* body1, * body2;


void Contact::calcRelativeVelocity() {
			XMFLOAT3 cross;
			XMStoreFloat3(&cross, XMVector3Cross(XMLoadFloat3(&body1->getAngularVelocity()), XMLoadFloat3(&subVector(c_position,body1->getPosition()))));
			XMFLOAT3 v1 = addVector(body1->getVelocity(), cross);
			XMStoreFloat3(&cross, XMVector3Cross(XMLoadFloat3(&body2->getAngularVelocity()), XMLoadFloat3(&subVector(c_position,body2->getPosition()))));
			XMFLOAT3 v2 = addVector(body2->getVelocity(), cross);
			v_relative_dot;
			v_relative = subVector(v1,v2);
			XMStoreFloat(&v_relative_dot, XMVector3Dot(c_normal,XMLoadFloat3(&v_relative)));

			if(v_relative_dot > 0 ) { //separating
			
			}
			else if ( v_relative_dot < 0) { //colliding
			}
			else { //sliding
			}
}

	
	Contact::Contact(XMFLOAT3 pos, XMVECTOR norm, rigidBody* rb1,rigidBody* rb2)
{
	c_position = pos;
	c_normal = norm;
	//depth = d;
	body1 = rb1;
	body2 = rb2;
}

Contact::Contact(void)
{
}


Contact::~Contact(void)
{
}