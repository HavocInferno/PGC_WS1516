#include "rigidBody.h"
#include <DirectXMath.h>

#include <iostream>
#include <iomanip>

using namespace DirectX;

#include "vectorOperations.h"
#include "MassPoint.h"
#include <list>

//float massInverse;
//XMFLOAT3 r_position;
//XMFLOAT3 r_velocity;
//XMMATRIX inertiaTensorInverse;
XMMATRIX currentInertiaInverse;
//XMFLOAT4 orientation;
//XMFLOAT3 angularVelocity;
//XMFLOAT3 angularMomentum;
//
//XMFLOAT3 forceAccumulator;
//XMFLOAT3 torqueAccumulator;
//
//XMMATRIX transform;
//XMFLOAT4 rotationQuaternion;
//std::list<MassPoint>* points;

void rigidBody::preCompute()
{
	r_position = angularMomentum = forceAccumulator = torqueAccumulator = XMFLOAT3(0,0,0);
	massInverse = 0.0f;
	float m = 0.0f;
	for(auto mp = points->begin(); mp != points->end(); mp++) {
		m += mp->mass;
		r_position = addVector(r_position, multiplyVector(mp->position, mp->mass));
	}
	massInverse = 1/m;
	m = m/12;
	float x = scale.x*scale.x, y = scale.y*scale.y, z = scale.z*scale.z;
	r_position = multiplyVector(r_position, massInverse);

	//inertiaTensorInverse = XMMATRIX(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
	XMMATRIX I =  DirectX::XMMatrixInverse(nullptr,XMMATRIX(m*(y+z),0,0,0,0,m*(x+z),0,0,0,0,m*(x+y),0,0,0,0,1));
	inertiaTensorInverse = currentInertiaInverse = I;
	for(auto mp = points->begin(); mp != points->end(); mp++) {
		//position to model view
		mp->position = subVector(mp->position, r_position);
		//inertiaTensorInverse += multiplyVectorTranspose(multiplyVector(mp->position,mp->mass),mp->position); 
		XMFLOAT3 L = XMFLOAT3(0,0,0);
	//	XMVECTOR x = XMLoadFloat3(&(mp->position));
	//	XMVECTOR mv = XMLoadFloat3();
		XMStoreFloat3(&L,DirectX::XMVector3Cross(XMLoadFloat3(&(mp->position)), XMLoadFloat3( &multiplyVector(mp->velocity,mp->mass))));
		angularMomentum = addVector(angularMomentum,L);
	}
	XMStoreFloat3(&angularVelocity, XMVector3Transform(XMLoadFloat3(&angularMomentum),I));
}

void rigidBody::computeInverInertTensAndAngVel()
{
	//INITIALIZATION
	//
	//inverse inertia tensor
	XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(XMLoadFloat4(&rotationQuaternion));
	//TODO: fix this more neatly.. There was a problem with inertiaTensor beeing private, so i just made a temp copy for now
	//currentInertiaInverse = XMMatrixMultiply(XMMatrixMultiply(rotationMatrix, inertiaTensorInverse), XMMatrixTranspose(rotationMatrix));
	XMMATRIX temp = inertiaTensorInverse;
	currentInertiaInverse = XMMatrixMultiply(rotationMatrix*temp,XMMatrixTranspose(rotationMatrix));
	//angular velocity
	XMStoreFloat3(&angularVelocity, XMVector3Transform(XMLoadFloat3(&angularMomentum), currentInertiaInverse));
	//angularVelocity = normalizeVector(angularVelocity);
}

void rigidBody::integrateValues(float timeStep) {
	XMFLOAT3 tmpFloat3 = torqueAccumulator = forceAccumulator = XMFLOAT3(0,0,0);
	
	//External forces
	for (auto mp = points->begin(); mp != points->end(); mp++) {
		//rotate local positions
		XMStoreFloat3(&mp->position, XMVector3Rotate(XMLoadFloat3(&mp->position), XMLoadFloat4(&rotationQuaternion)));

		forceAccumulator = addVector(forceAccumulator, mp->force);
		XMStoreFloat3(&tmpFloat3, XMVector3Cross(XMLoadFloat3(&mp->position), XMLoadFloat3(&mp->force)));
		torqueAccumulator = addVector(torqueAccumulator, tmpFloat3);
		//nullify the force
		mp->force = XMFLOAT3(0.f, 0.f, 0.f);
	}

	//Euler step
	r_position = addVector(r_position, multiplyVector(r_velocity, timeStep));
	r_velocity = addVector(r_velocity, multiplyVector(forceAccumulator, timeStep * massInverse));
	
	//Quaternion
	//
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
					// + original rotation
					XMLoadFloat4(&rotationQuaternion))
		)
	);

	angularMomentum = addVector(angularMomentum, multiplyVector(torqueAccumulator, timeStep));
	computeInverInertTensAndAngVel();


	//World position
	//r_position = XMFLOAT3(.0f, .0f, .0f);
	for (auto mp = points->begin(); mp != points->end(); mp++) {
		XMStoreFloat3(&mp->worldPosition, XMVector3Rotate(XMLoadFloat3(&mp->position), XMLoadFloat4(&rotationQuaternion)));
		mp->worldPosition = addVector(r_position, mp->worldPosition);
		//
		//TODO: apply rotation to each point?
	}
}

void rigidBody::setPosition(XMFLOAT3 newPos) {
	XMFLOAT3 centerOffset = subVector(newPos,r_position);
	r_position = addVector(r_position,centerOffset);
	for(auto mp = points->begin(); mp != points->end(); mp++) {
		mp->worldPosition = addVector(centerOffset,mp->worldPosition);
	}

}

void rigidBody::setLinearVelocity(XMFLOAT3 lV) {
	r_velocity = lV;
}
void rigidBody::setAngularMomentum(XMFLOAT3 aM) {
	angularMomentum = aM;
}

XMFLOAT3 rigidBody::getScale() {
	return scale;
}

XMFLOAT3 rigidBody::getPosition() {
	return r_position;
}

XMFLOAT3 rigidBody::getVelocity() {
	return r_velocity;
}

XMFLOAT3 rigidBody::getAngularVelocity() {
	return angularVelocity;
}
XMFLOAT3 rigidBody::getAngularMomentum() {
	return angularMomentum;
} 

XMFLOAT4 rigidBody::getRotationQuaternion() {
	return rotationQuaternion;
}
float rigidBody::getMassInverse() {
	return massInverse;
} 

XMMATRIX rigidBody::getInertiaTensorInverse() {
	return inertiaTensorInverse;
}

std::vector<MassPoint>* rigidBody::getMassPoints() {
	return points;
}

rigidBody::rigidBody(void)
{
	points = new std::vector<MassPoint>();
}

rigidBody::rigidBody(std::vector<MassPoint>* pointList, XMFLOAT3 vel, XMFLOAT3 rotation, XMFLOAT3 scale = XMFLOAT3(1.f, 1.f, 1.f)) {
	this->scale = scale;
	points = pointList;
	r_velocity = vel;
	XMStoreFloat4(&rotationQuaternion,XMQuaternionRotationRollPitchYaw(rotation.x,rotation.y, rotation.z));
	preCompute();
	computeInverInertTensAndAngVel();
}

rigidBody::~rigidBody(void)
{
}
