#pragma once

#include "IParticleRenderer.h"
#include <Core/GenericSingleton.h>

class ParticleRenderer : public IParticleRenderer, public GenericSingleton<ParticleRenderer>
{
	friend GenericSingleton<ParticleRenderer>;

public:
	void Draw(Spark *spark, const sm::Matrix &viewMatrix);

private:
	ParticleRenderer();
};

