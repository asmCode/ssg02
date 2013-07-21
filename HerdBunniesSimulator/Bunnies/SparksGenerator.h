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
	void SetSourceDirection(const sm::Vec3 &direction, float spreadAngle); // spreadAngle is a fake, should be cone angle
	void SetInitialSpeed(float minSpeed, float maxSpeed);
	void SetSparksPerSecond(float sparksPerSecond);

	void EnableSparksSource();
	void DisableSparksSource();

private:
	static const uint32_t DefaultSparksPerSecond;
	static const float DefaultInitialMinSpeed;
	static const float DefaultInitialMaxSpeed;
	static const float DefaultSpreadAngle;

	uint32_t m_maxParticesCount;
	uint32_t m_activeParticles; // performance purpose

	IParticleRenderer *m_particleRenderer;
	IParticleFactory *m_particleFactory;

	bool m_sparksSourceEnabled;

	sm::Vec3 m_sourcePosition;
	sm::Vec3 m_direction;
	float m_spreadAngle;
	uint32_t m_sparksPerSeconds;
	float m_initialMinSpeed;
	float m_initialMaxSpeed;

	uint32_t m_liveSparksCount;
	float m_sparksToStart;

	Spark **m_sparks;

	void StartParticle(Spark *particle);
};

