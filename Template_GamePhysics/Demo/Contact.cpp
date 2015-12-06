#include "Contact.h"
#include <DirectXMath.h>
using namespace DirectX;

#include "vectorOperations.h"
#include "rigidBody.h"

XMFLOAT3 c_position;
XMVECTOR c_normal;
float depth;
rigidBody* body1, * body2;
float impulse;


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


void Contact::calculateImpulse() {
	float c = 0; //this should determine if the body is elastic or plastic.. for now i'll leave it as plastic!

	float ma = body1->getMassInverse(), mb = body2->getMassInverse();

	float numerator = -(1+c)*v_relative_dot;

	XMVECTOR tempVec_a, tempVec_b, center_1, center_2;
	center_1 = XMLoadFloat3(body1->getPosition);
	center_2 = XMLoadFloat3(body2->getPosition);
	tempVec_a = XMVector3Transform(XMVector3Cross(XMVector3Cross(center_1,c_normal),center_1),body1->getInertiaTensorInverse());
	tempVec_b = XMVector3Transform(XMVector3Cross(XMVector3Cross(center_2,c_normal),center_2),body1->getInertiaTensorInverse());
	tempVec_a = XMVector3Dot(tempVec_a+tempVec_b,c_normal);

	float temp;
	XMStoreFloat(&temp, tempVec_a);
	float denominator = ma + mb + temp;

	impulse = numerator / denominator;


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