// header file:
#include <DirectXMath.h>
using namespace DirectX;

//if the normalWorld == XMVectorZero(), no collision
struct CollisionInfo{ // the return structure, with these values, you should be able to calculate the impulse
	bool isValid;                          // whether there is a collision point, true for yes
	DirectX::XMVECTOR collisionPointWorld; // the position of the collision point in world space
	DirectX::XMVECTOR normalWorld;         // the direction of the impulse to A, negative of the collision face of A
};

// source file:
/* params:
obj2World_A, the transfer matrix from object space of A to the world space
obj2World_B, the transfer matrix from object space of B to the world space
xlen_A, ylen_A, zlen_A, the length of the edges of A
xlen_B, ylen_B, zlen_B, the length of the edges of B
*/
inline CollisionInfo checkCollision(const XMMATRIX obj2World_A, const XMMATRIX obj2World_B, 
	float xlen_A, float ylen_A, float zlen_A, float xlen_B, float ylen_B, float zlen_B) {

	// the transfer matrix from the world space to object space of A:
	const XMMATRIX world2Obj_A = XMMatrixInverse(nullptr, obj2World_A);
	// half edges:
	const float edgeA[3] = {xlen_A / 2.0f, ylen_A / 2.0f, zlen_A / 2.0f};
	const float edgeB[3] = {xlen_B / 2.0f, ylen_B / 2.0f, zlen_B / 2.0f};

	// transfer all values to the obj space of A:
	const XMMATRIX objB2objA = obj2World_B * world2Obj_A;
	const XMVECTOR centerB_objA = XMVector3Transform(XMVectorZero(), objB2objA);
	XMVECTOR edgeB_objA[3];
	for (size_t i = 0; i < 3; ++i)
		edgeB_objA[i] = XMVector3TransformNormal( XMVectorSetByIndex(XMVectorZero(), edgeB[i], i), objB2objA);
	
	const XMVECTOR cornersB_objA[8] = { // corners of body B in object space A
		centerB_objA - edgeB_objA[0] - edgeB_objA[1] - edgeB_objA[2],
		centerB_objA + edgeB_objA[0] - edgeB_objA[1] - edgeB_objA[2],
		centerB_objA - edgeB_objA[0] + edgeB_objA[1] - edgeB_objA[2],
		centerB_objA + edgeB_objA[0] + edgeB_objA[1] - edgeB_objA[2],
		centerB_objA - edgeB_objA[0] - edgeB_objA[1] + edgeB_objA[2],
		centerB_objA + edgeB_objA[0] - edgeB_objA[1] + edgeB_objA[2],
		centerB_objA - edgeB_objA[0] + edgeB_objA[1] + edgeB_objA[2],
		centerB_objA + edgeB_objA[0] + edgeB_objA[1] + edgeB_objA[2]
	};
	
	CollisionInfo info;
	info.isValid = false;
	info.collisionPointWorld = XMVectorZero();
	info.normalWorld = XMVectorZero();
	
	// check every corners of body B
	for (size_t i = 0; i < 8; ++i){
		if(XMVector3InBounds(cornersB_objA[i], XMVectorSet(edgeA[0], edgeA[1], edgeA[2], 0.0f))){
			//collision! find the closest face
			int   normalIndex = 0;      
			float mindis      = FLT_MAX;
			float disSign     = 1.0;
			
			for (int j = 0; j < 3; ++j){
				float curpos = XMVectorGetByIndex(cornersB_objA[i], j);
				float curdis = edgeA[j] - abs(curpos);
				
				if( curdis < mindis ) {
					normalIndex = j;
					mindis      = curdis;
					disSign     = (curpos >= 0.0f) ? -1.0f : 1.0f;
				}
			}
			// assert(normalIndex != -1);
			info.isValid = true;
			// transform collision points from object space into world space
			info.collisionPointWorld = XMVector3Transform(cornersB_objA[i], obj2World_A);
			// the direction of the collision is opposite to the normal of the collision 
			// face on A (the one nearest to the corner(B))
			info.normalWorld = XMVector3Normalize( XMVector3TransformNormal
				( XMVectorSetByIndex(XMVectorZero(), disSign, normalIndex), obj2World_A ) );
			
			return info;
		}
	}
	
	return CollisionInfo(); // if the info.normal == XMVectorZero(), no collision
}

/*
// simple examples, suppose that boxes A and B are at the original point and have no rotation
// case 1, collide at a corner of Box B:
XMMATRIX AM = XMMatrixTranslation(0.2f,5.0f,1.0f);// box A moves (0.2f,5.0f,1.0f) from origin
XMMATRIX BM = XMMatrixRotationZ(3.141592f/4.0f);  // box B rotates 45 degree around axis z
// box A size(9,2,3), box B size(5.657, 5.657, 2)
CollisionInfo simpletest = checkCollision(AM, BM, 9.0f, 2.0f, 3.0f, 5.657f, 5.657f, 2.0f); // should find out a collision here
if (!simpletest.isValid){
		simpletest = checkCollision(BM, AM, 5.657f, 5.657f, 2.0f, 9.0f, 2.0f, 3.0f);
		simpletest.normalWorld = -simpletest.normalWorld;// we compute the impulse to A
}
if (!simpletest.isValid)
	std::printf("No Collision\n");
else{
	std::printf("collision detected at normal: %f, %f, %f\n",XMVectorGetX(simpletest.normalWorld), XMVectorGetY(simpletest.normalWorld), XMVectorGetZ(simpletest.normalWorld));
	std::printf("collision point : %f, %f, %f\n",XMVectorGetX(simpletest.collisionPointWorld), XMVectorGetY(simpletest.collisionPointWorld), XMVectorGetZ(simpletest.collisionPointWorld));
}
// case 1 result:
// collision detected at normal: 0.000000, 1.000000, 0.000000
// collision point : 0.000001, 4.000103, 1.000000

// case 2, collide at a corner of Box A:
XMMATRIX AM = XMMatrixRotationZ(3.141592f/4.0f);// box A first rotates 45 degree around axis z
AM = AM * XMMatrixTranslation(-2.0f,0.0f,1.0f); // box A then moves (-2.0f,0.0f,1.0f) from origin, (-2.0f,0.0f,1.0f) is also the centre position of A in world space
XMMATRIX BM = XMMatrixRotationZ(3.141592f/2.0f);// box B first rotates 90 degree around axis z
BM = BM * XMMatrixTranslation(1.0f,0.5f,0.0f); // box B then moves (1.0f,0.5f,0.0f) from origin, (1.0f,0.5f,0.0f) is also the centre position of B in world space
// box A size(2.829,2.829,2), box B size(9, 2, 4)
CollisionInfo simpletest = checkCollision(AM, BM, 2.829f, 2.829f, 2.0f, 9.0f, 2.0f, 4.0f); // should find no collision here
if (!simpletest.isValid){
	simpletest = checkCollision(BM, AM, 9.0f, 2.0f, 4.0f, 2.829f, 2.829f, 2.0f);           // should find out a collision here
	simpletest.normalWorld = -simpletest.normalWorld; // we compute the impulse to A
}
if (!simpletest.isValid)
	std::printf("No Collision\n");
else{
	std::printf("collision detected at normal: %f, %f, %f\n",XMVectorGetX(simpletest.normalWorld), XMVectorGetY(simpletest.normalWorld), XMVectorGetZ(simpletest.normalWorld));
	std::printf("collision point : %f, %f, %f\n",XMVectorGetX(simpletest.collisionPointWorld), XMVectorGetY(simpletest.collisionPointWorld), XMVectorGetZ(simpletest.collisionPointWorld));
}
// case 2 result:
// collision detected at normal: -1.000000, 0.000000, 0.000000
// collision point : 0.000405, -0.000000, 0.000000
*/