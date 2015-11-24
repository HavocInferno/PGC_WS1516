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
static XMMATRIX multiplyVectorTranspose(XMFLOAT3 vec, XMFLOAT3 vecT)
{
	return XMMATRIX(vec.x*vecT.x,vec.x*vecT.y,vec.x*vecT.z,0.0f,vec.y*vecT.x,vec.y*vecT.y,vec.y*vecT.z,0.0f,vec.z*vecT.x,vec.z*vecT.y,vec.z*vecT.z,0.0f,0.0f,0.0f,0.0f,1.0f);
}

	
#endif
