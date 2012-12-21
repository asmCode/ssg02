#pragma once

#include <Math/Vec3.h>

class IBullet
{
public:
	virtual void Update(float time, float seconds) = 0;
	virtual void Draw(float time, float seconds) = 0;
};

