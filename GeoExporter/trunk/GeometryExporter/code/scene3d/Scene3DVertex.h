#pragma once

#include <Math\Vec3.h>
#include <Math\Vec2.h>

class Scene3DVertex
{
public:
	sm::Vec3 normal;
	sm::Vec3 tangent;
	sm::Vec2 coords;
	sm::Vec3 position;
};
