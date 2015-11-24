#include "Contact.h"
#include <DirectXMath.h>
using namespace DirectX;

#include "vectorOperations.h"
#include "rigidBody.h"

XMFLOAT3 position;
XMFLOAT3 normal;
float depth;
rigidBody body1, body2;

Contact::Contact(void)
{
}


Contact::~Contact(void)
{
}
