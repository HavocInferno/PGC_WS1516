#include "Contact.h"
#include <DirectXMath.h>
using namespace DirectX;

#include "vectorOperations.h"
#include "rigidBody.h"

XMFLOAT3 c_position;
XMFLOAT3 c_normal;
float depth;
rigidBody body1, body2;

Contact::Contact(void)
{
}


Contact::~Contact(void)
{
}
