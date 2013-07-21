#pragma once

#include "IParticleRenderer.h"

class ParticleRenderer : public IParticleRenderer
{
public:
	void Draw(Spark *spark, const sm::Matrix &viewMatrix);
};

