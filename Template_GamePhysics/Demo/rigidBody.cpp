#include "rigidBody.h"
#include <DirectXMath.h>
using namespace DirectX;

#include "vectorOperations.h"
#include "MassPoint.h"
#include <list>

float massInverse;
XMFLOAT3 r_position;
XMFLOAT3 r_velocity;
XMMATRIX inertiaTensorInverse;
XMFLOAT4 orientation;
XMFLOAT3 angularVelocity;
XMFLOAT3 angularMomentum;

XMFLOAT3 forceAccumulator;
XMFLOAT3 torqueAccumulator;

XMMATRIX transform;
XMFLOAT4 rotationQuaternion;
std::list<MassPoint>* points;

void rigidBody::preCompute()
{
	r_position = angularMomentum =XMFLOAT3(0,0,0);
	massInverse = 0.0f;
	for(auto mp = points->begin(); mp != points->end(); mp++) {
		massInverse += mp->mass;
		r_position = addVector(r_position, multiplyVector(mp->position, mp->mass));
	}
	massInverse = 1/massInverse;
	r_position = multiplyVector(r_position, massInverse);
	inertiaTensorInverse = XMMATRIX(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
	for(auto mp = points->begin(); mp != points->end(); mp++) {
		mp->position = subVector(mp->position, r_position);
		inertiaTensorInverse += multiplyVectorTranspose(multiplyVector(mp->position,mp->mass),mp->position); 
		XMFLOAT3 L = XMFLOAT3(0,0,0);
	//	XMVECTOR x = XMLoadFloat3(&(mp->position));
	//	XMVECTOR mv = XMLoadFloat3();
		XMStoreFloat3(&L,XMVector3Cross(XMLoadFloat3(&(mp->position)), XMLoadFloat3( &multiplyVector(mp->velocity,mp->mass))));
		angularMomentum = addVector(angularMomentum,L);
	}
	XMStoreFloat3(&angularVelocity, XMVector3Transform(XMLoadFloat3(&angularMomentum),inertiaTensorInverse));
}

rigidBody::rigidBody(void)
{
	points = new std::list<MassPoint>();
}

rigidBody::rigidBody(std::list<MassPoint>* pointList, XMFLOAT3 vel, XMFLOAT3 rotation)
{
	points = pointList;
	r_velocity = vel;
	preCompute();
	XMStoreFloat4(&rotationQuaternion,XMQuaternionRotationRollPitchYaw(rotation.x,rotation.y, rotation.z));
}

rigidBody::~rigidBody(void)
{
}
