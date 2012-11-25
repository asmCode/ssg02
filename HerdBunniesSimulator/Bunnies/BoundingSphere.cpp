#include "BoundingSphere.h"
#include <assert.h>

BoundingSphere::BoundingSphere(const sm::Vec3 &center, float radius) :
	m_center(center),
	m_radius(radius)
{
}

bool BoundingSphere::IsCollision(const BoundingSphere &bs1, const BoundingSphere &bs2)
{
	return (bs1.m_center - bs2.m_center).GetLength() < (bs1.m_radius + bs2.m_radius);
}

