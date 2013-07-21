#pragma once

#include <Math\Vec3.h>
#include "ThrowTrajectory.h"

class Spark
{
public:
	Spark();
	virtual ~Spark() {};
	
	ThrowTrajectory m_throw;
	
	float m_liteTime;
	bool m_isUsed;
};

