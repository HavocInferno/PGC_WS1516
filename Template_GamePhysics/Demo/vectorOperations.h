#pragma once
#ifndef VECTOR_HEADER
#define VECTOR_HEADER

static XMFLOAT3 addVector(XMFLOAT3 float1, XMFLOAT3 float2)
{
	return XMFLOAT3(float1.x+float2.x, float1.y+float2.y, float1.z+float2.z);
}
static XMFLOAT3 subVector(XMFLOAT3 float1, XMFLOAT3 float2)
{
	return XMFLOAT3(float1.x-float2.x, float1.y-float2.y, float1.z-float2.z);
}
static XMFLOAT3 multiplyVector(XMFLOAT3 vector, float factor)
{
	return XMFLOAT3(vector.x*factor, vector.y*factor, vector.z*factor);
}
static XMFLOAT3 invertVector(XMFLOAT3 vector, float factor)
{
	return XMFLOAT3(factor/vector.x, factor/vector.y, factor/vector.z);
}
static float vectorLength(XMFLOAT3 vector)
{
	return sqrtf(vector.x*vector.x+vector.y*vector.y+vector.z*vector.z);
}
static XMFLOAT3 normalizeVector(XMFLOAT3 vector)
{
	return multiplyVector(vector,1/vectorLength(vector));
}
	
#endif
