#include "SparksGenerator.h"
#include "IParticleRenderer.h"
#include "IParticleFactory.h"
#include "Spark.h"
#include <Utils/Randomizer.h>
#include <memory>
#include <assert.h>

const uint32_t SparksGenerator::DefaultSparksPerSecond = 10;
const float SparksGenerator::DefaultInitialMinSpeed = 5.0f;
const float SparksGenerator::DefaultInitialMaxSpeed = 10.0f;
const float SparksGenerator::DefaultSpreadAngle = 1.0f;

SparksGenerator::SparksGenerator(uint32_t maxSpritesCount,
								 IParticleRenderer *particleRenderer,
								 IParticleFactory *particleFactory) :
	m_maxParticesCount(maxSpritesCount),
	m_particleRenderer(particleRenderer),
	m_particleFactory(particleFactory),
	m_activeParticles(0),
	m_sparksSourceEnabled(true),
	m_liveSparksCount(0),
	m_sparksToStart(0.0f),
	m_sourcePosition(sm::Vec3(0, 0, 0)),
	m_spreadAngle(DefaultSpreadAngle),
	m_sparksPerSeconds(DefaultSparksPerSecond),
	m_initialMinSpeed(DefaultInitialMinSpeed),
	m_initialMaxSpeed(DefaultInitialMaxSpeed)
{
	m_sparks = new Spark*[maxSpritesCount];
	
	for (uint32_t i = 0; i < m_maxParticesCount; i++)
		if (m_particleFactory != NULL)
			m_sparks[i] = m_particleFactory->Create();
		else
			m_sparks[i] = new Spark();
}

SparksGenerator::~SparksGenerator(void)
{
	for (uint32_t i = 0; i < m_maxParticesCount; i++)
		delete m_sparks[i];

	delete [] m_sparks;
}

void SparksGenerator::Update(float seconds)
{
	if (m_sparksSourceEnabled)
		m_sparksToStart += static_cast<float>(m_sparksPerSeconds) * seconds;

	if (m_activeParticles == 0 && m_sparksToStart < 1.0f)
		return;

	for (uint32_t i = 0; i < m_maxParticesCount; i++)
	{
		// spark is living
		if (m_sparks[i]->m_isUsed && m_sparks[i]->m_liteTime >= 0.0f)
		{
			m_sparks[i]->m_liteTime -= seconds;
			m_sparks[i]->m_throw.Update(seconds);
		}
		// spark just died
		else if (m_sparks[i]->m_isUsed && m_sparks[i]->m_liteTime < 0.0f)
		{
			m_activeParticles--;
			m_sparks[i]->m_isUsed = false;
		}

		if (m_sparksSourceEnabled && !m_sparks[i]->m_isUsed && m_sparksToStart >= 1.0f)
		{
			m_activeParticles++;
			StartParticle(m_sparks[i]);
			m_sparksToStart -= 1.0f;
		}
	}
}

void SparksGenerator::Draw(float seconds,
						   const sm::Matrix &proj,
						   const sm::Matrix &view)
{
	if (m_activeParticles == 0)
		return;

	for (uint32_t i = 0; i < m_maxParticesCount; i++)
	{
		if (m_sparks[i]->m_isUsed)
		{
			float power = 1.0f;
			if (m_sparks[i]->m_liteTime < 0.5f && m_sparks[i]->m_liteTime >= 0.0f)
			{
				power = m_sparks[i]->m_liteTime / 0.5f;
				assert(power >= 0.0f && power <= 1.0f);
			}
			if (m_sparks[i]->m_liteTime <= 0.0f)
				power = 0.0f;

			m_particleRenderer->Draw(m_sparks[i], view);
		}
	}
}

void SparksGenerator::SetSourcePosition(const sm::Vec3 &position)
{
	m_sourcePosition = position;
}

void SparksGenerator::SetSourceDirection(const sm::Vec3 &direction, float spreadAngle)
{
	m_direction = direction;
	m_spreadAngle = spreadAngle;
}

void SparksGenerator::SetInitialSpeed(float minSpeed, float maxSpeed)
{
	m_initialMinSpeed = minSpeed;
	m_initialMaxSpeed = maxSpeed;
}

void SparksGenerator::SetSparksPerSecond(float sparksPerSecond)
{
	m_sparksPerSeconds = sparksPerSecond;
}

void SparksGenerator::EnableSparksSource()
{
	m_sparksSourceEnabled = true;
}

void SparksGenerator::DisableSparksSource()
{
	m_sparksSourceEnabled = false;
	m_sparksToStart = 0.0f;
}

void SparksGenerator::StartParticle(Spark *particle)
{
	static Randomizer random;

	sm::Vec3 spreadVector = sm::Vec3(
		random.GetFloat(-m_spreadAngle, m_spreadAngle),
		random.GetFloat(-m_spreadAngle, m_spreadAngle),
		random.GetFloat(-m_spreadAngle, m_spreadAngle));

	float speed = random.GetFloat(m_initialMinSpeed, m_initialMaxSpeed);

	particle->m_throw.Throw(m_sourcePosition, m_direction + spreadVector, speed, 30.0f);
	particle->m_liteTime = random.GetFloat(0.4f, 1.2f);
	particle->m_isUsed = true;
}

