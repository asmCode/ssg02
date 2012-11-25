#pragma once

#include <math\Vec3.h>

class BoundingSphere
{
public:
	float m_radius;
	sm::Vec3 m_center;

	BoundingSphere(const sm::Vec3 &center, float radius);

	static bool IsCollision(const BoundingSphere &bs1, const BoundingSphere &bs2);
};
