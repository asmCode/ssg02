#pragma once

#include "Spark.h"
#include <Math\Vec3.h>
#include <Math\Matrix.h>
#include <stdint.h>

class IParticleRenderer;
class IParticleFactory;

class SparksGenerator
{
public:
	SparksGenerator(
		uint32_t maxParticlesCount,
		IParticleRenderer *particleRenderer,
		IParticleFactory *particleFactory);

	~SparksGenerator(void);

	void Update(float seconds);
	void Draw(float seconds,
		const sm::Matrix &proj,
		const sm::Matrix &view);

	void SetSourcePosition(const sm::Vec3 &position);

	void EnableSparksSource();
	void DisableSparksSource();

private:
	static const uint32_t DefaultSparksPerSecond = 400;

	uint32_t m_maxParticesCount;
	uint32_t m_activeParticles; // performance purpose

	IParticleRenderer *m_particleRenderer;
	IParticleFactory *m_particleFactory;

	bool m_sparksSourceEnabled;

	sm::Vec3 m_sourcePosition;

	uint32_t m_liveSparksCount;
	float m_sparksToStart;

	Spark **m_sparks;
};

