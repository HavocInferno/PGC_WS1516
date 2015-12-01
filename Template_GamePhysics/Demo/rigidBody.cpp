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
	r_position = angularMomentum = forceAccumulator = torqueAccumulator = XMFLOAT3(0,0,0);
	massInverse = 0.0f;
	for(auto mp = points->begin(); mp != points->end(); mp++) {
		massInverse += mp->mass;
		r_position = addVector(r_position, multiplyVector(mp->position, mp->mass));
	}
	massInverse = 1/massInverse;
	r_position = multiplyVector(r_position, massInverse);

	inertiaTensorInverse = XMMATRIX(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
	for(auto mp = points->begin(); mp != points->end(); mp++) {
		//mp->position = subVector(mp->position, r_position);
		inertiaTensorInverse += multiplyVectorTranspose(multiplyVector(mp->position,mp->mass),mp->position); 
		XMFLOAT3 L = XMFLOAT3(0,0,0);
	//	XMVECTOR x = XMLoadFloat3(&(mp->position));
	//	XMVECTOR mv = XMLoadFloat3();
		XMStoreFloat3(&L,XMVector3Cross(XMLoadFloat3(&(mp->position)), XMLoadFloat3( &multiplyVector(mp->velocity,mp->mass))));
		angularMomentum = addVector(angularMomentum,L);
	}
	XMStoreFloat3(&angularVelocity, XMVector3Transform(XMLoadFloat3(&angularMomentum),inertiaTensorInverse));

	//INITIALIZATION
	//
	//inverse inertia tensor
	XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(XMLoadFloat4(&rotationQuaternion));
	inertiaTensorInverse = XMMatrixMultiply(XMMatrixMultiply(rotationMatrix, inertiaTensorInverse), XMMatrixTranspose(rotationMatrix));
	//angular velocity
	XMStoreFloat3(&angularVelocity, XMVector3Transform(XMLoadFloat3(&angularMomentum), inertiaTensorInverse));
}

void rigidBody::integrateValues(float timeStep) {
	XMFLOAT3* tempFloat3 = &forceAccumulator;
	XMMATRIX rotationMatrix;

	//External forces
	for (auto mp = points->begin(); mp != points->end(); mp++) {
		forceAccumulator = addVector(forceAccumulator, mp->force);
		XMStoreFloat3(tempFloat3, XMVector3Cross(XMLoadFloat3(&mp->position), XMLoadFloat3(&mp->force)));
		torqueAccumulator = addVector(torqueAccumulator, *tempFloat3);
	}

	//Euler step
	r_position = addVector(r_position, multiplyVector(r_velocity, timeStep));
	r_velocity = addVector(r_velocity, multiplyVector(forceAccumulator, timeStep * massInverse));

	//Quaternion
	XMStoreFloat4(&rotationQuaternion, 
		XMQuaternionNormalize(
			//(0,w)r * h/2 + original rotation
			XMVectorAdd(
					// (0,w)r * h/2
					XMVectorScale(
						// (0,w)r
						XMQuaternionMultiply(
							XMLoadFloat4(&XMFLOAT4(angularVelocity.x, angularVelocity.y, angularVelocity.z, .0f)), 
							XMLoadFloat4(&rotationQuaternion))
						, timeStep / 2), 
					XMLoadFloat4(&rotationQuaternion))));
		
	angularMomentum = addVector(angularMomentum, multiplyVector(torqueAccumulator, timeStep));
	//inverse inertia tensor
	rotationMatrix = XMMatrixRotationQuaternion(XMLoadFloat4(&rotationQuaternion));
	inertiaTensorInverse = XMMatrixMultiply(XMMatrixMultiply(rotationMatrix, inertiaTensorInverse), XMMatrixTranspose(rotationMatrix));
	//angular velocity
	XMStoreFloat3(&angularVelocity, XMVector3Transform(XMLoadFloat3(&angularMomentum), inertiaTensorInverse));

	//World position
	r_position = XMFLOAT3(.0f, .0f, .0f);
	for (auto mp = points->begin(); mp != points->end(); mp++) {
		XMStoreFloat3(&mp->position, XMVector3Rotate(XMLoadFloat3(&mp->position), XMLoadFloat4(&rotationQuaternion)));
		//r_position = addVector(r_position, mp->position);
		//TODO: do we need to compute v for each point?
	}
}

rigidBody::rigidBody(void)
{
	points = new std::list<MassPoint>();
}

rigidBody::rigidBody(std::list<MassPoint>* pointList, XMFLOAT3 vel, XMFLOAT3 rotation, XMFLOAT3 scale = XMFLOAT3(1.f, 1.f, 1.f)) {
	this->scale = scale;
	points = pointList;
	r_velocity = vel;
	preCompute();
	XMStoreFloat4(&rotationQuaternion,XMQuaternionRotationRollPitchYaw(rotation.x,rotation.y, rotation.z));
}

rigidBody::~rigidBody(void)
{
}
