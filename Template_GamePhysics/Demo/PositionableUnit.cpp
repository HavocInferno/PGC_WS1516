#pragma once

#include <DirectXMath.h>
#include <iostream>

using namespace DirectX;

class SpringPoint;

class PositionableUnit {
public:
	XMFLOAT3 gp_position;

	PositionableUnit operator= (const PositionableUnit& pu) {
		std::cout << "operator=" << std::endl;
		gp_position.x = pu.gp_position.x;
		gp_position.y = pu.gp_position.y;
		gp_position.z = pu.gp_position.z;
	}
};