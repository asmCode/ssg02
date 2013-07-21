#include "SparksGenerator.h"
#include "IParticleRenderer.h"
#include "IParticleFactory.h"
#include "Spark.h"
#include <memory>
#include <assert.h>

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
	m_sourcePosition(sm::Vec3(0, 0, 0))
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
		m_sparksToStart += static_cast<float>(DefaultSparksPerSecond) * seconds;

	if (m_activeParticles == 0 && m_sparksToStart < 1.0f)
		return;

	for (uint32_t i = 0; i < m_maxParticesCount; i++)
	{
		// spark is living
		if (m_sparks[i]->m_isUsed && m_sparks[i]->m_liteTime >= 0.0f)
		{
			m_sparks[i]->m_liteTime -= seconds;
			m_sparks[i]->m_position += m_sparks[i]->m_moveTarget * seconds * 40.0f;
			m_sparks[i]->m_moveTarget = (m_sparks[i]->m_moveTarget + (sm::Vec3(0, -9.8f, 0.0f) * seconds));
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
			m_sparks[i]->Start(m_sourcePosition);
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

void SparksGenerator::EnableSparksSource()
{
	m_sparksSourceEnabled = true;
}

void SparksGenerator::DisableSparksSource()
{
	m_sparksSourceEnabled = false;
	m_sparksToStart = 0.0f;
}

