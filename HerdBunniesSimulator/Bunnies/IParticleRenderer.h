#pragma once

#include <Math\Matrix.h>

class Spark;

class IParticleRenderer
{
public:
	virtual void Draw(Spark *spark, const sm::Matrix &viewMatrix) = 0;
};

