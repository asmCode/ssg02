#include "BunniesManager.h"
#include "HealthyBunny.h"
#include "../BunniesView/IShapesRenderer.h"
#include <Utils/Randomizer.h>

#include <assert.h>

BunniesManager::BunniesManager(IShapesRenderer *shapesRenderer) :
	m_shapesRenderer(shapesRenderer)
{
	assert(m_shapesRenderer != NULL);

	for (uint32_t i = 0; i < MaxBunniesCount; i++)
		m_healthyBunnies[i] = new HealthyBunny();
}

BunniesManager::~BunniesManager(void)
{
}

void BunniesManager::ClearBunnies()
{
	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		m_healthyBunnies[i]->Reset();
	}
}

void BunniesManager::ResetForNewGame(uint32_t healthyBunniesCount)
{
	static Randomizer random;

	assert(healthyBunniesCount < MaxBunniesCount);

	ClearBunnies();

	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		if (i < healthyBunniesCount)
		{
			sm::Vec3 startPos;
			startPos.x = random.GetFloat(-50.0f, 50.0f);
			startPos.y = 0.0f;
			startPos.z = random.GetFloat(-50.0f, 50.0f);

			m_healthyBunnies[i]->ActivateOnStart(startPos);
		}
	}
}

void BunniesManager::Update(float time, float seconds)
{
	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		if (m_healthyBunnies[i]->IsActive())
			m_healthyBunnies[i]->Update(time, seconds);
	}
}

void BunniesManager::Draw(float time, float seconds)
{
	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		if (m_healthyBunnies[i]->IsActive())
			m_shapesRenderer->DrawHealthyBunny(m_healthyBunnies[i]);
	}
}

