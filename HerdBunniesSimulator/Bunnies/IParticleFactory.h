#pragma once

class Spark;

class IParticleFactory
{
public:
	virtual ~IParticleFactory() {};

	virtual Spark* Create();
};

