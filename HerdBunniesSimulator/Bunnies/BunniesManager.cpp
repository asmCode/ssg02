#include "BunniesManager.h"
#include "HealthyBunny.h"
#include "IBunnyState.h"
#include "GoingToReproduction.h"
#include "../BunniesView/IShapesRenderer.h"
#include <Utils/Randomizer.h>

#include <assert.h>

BunniesManager::BunniesManager(IShapesRenderer *shapesRenderer) :
	m_shapesRenderer(shapesRenderer),
	m_reproduceColldown(0.0f),
	m_reproduceDelay(5.0f) // TOOD
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

bool BunniesManager::CheckCollision(const IBunny *bunny)
{
	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		if (m_healthyBunnies[i]->IsActive())
		{
			if (bunny == m_healthyBunnies[i])
				continue;

			float bunnyRadius = 0.4f; //TODO
			if ((m_healthyBunnies[i]->GetPosition() - bunny->GetPosition()).GetLength() < (bunnyRadius * 2))
				return true;
		}
	}

	return false;
}

bool BunniesManager::CheckCollision(const sm::Vec3 &position, float radius, const IBunny *excludeFromTest)
{
	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		if (m_healthyBunnies[i]->IsActive())
		{
			if (excludeFromTest == m_healthyBunnies[i])
				continue;

			float bunnyRadius = 0.4f; //TODO
			if ((m_healthyBunnies[i]->GetPosition() - position).GetLength() < (bunnyRadius + radius))
				return true;
		}
	}

	return false;
}

void BunniesManager::Update(float time, float seconds)
{
	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		if (m_healthyBunnies[i]->IsActive())
			m_healthyBunnies[i]->Update(time, seconds);
	}

	m_reproduceColldown += seconds;

	if (ShouldGoToReproduce())
		GoToReproduce();
}

void BunniesManager::Draw(float time, float seconds)
{
	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		if (m_healthyBunnies[i]->IsActive())
			m_shapesRenderer->DrawHealthyBunny(m_healthyBunnies[i]);
	}
}

bool BunniesManager::ShouldGoToReproduce()
{
	if (m_reproduceColldown >= m_reproduceDelay)
		return true;

	return false;
}

void BunniesManager::GoToReproduce()
{
	m_reproduceColldown = 0.0f;

	HealthyBunny *bunny1 = NULL;
	HealthyBunny *bunny2 = NULL;

	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		if (m_healthyBunnies[i]->IsActive())
		{
			if (m_healthyBunnies[i]->CanReproduce())
			{
				if (bunny1 == NULL) // found first one
					bunny1 = m_healthyBunnies[i];
				else if (bunny2 == NULL) // found second one
					bunny2 = m_healthyBunnies[i];
				
				if (bunny1 != NULL && bunny2 != NULL)
				{
					bunny1->SetReproductionPartner(bunny2);
					bunny1->SetState(GoingToReproduction::GetInstance());

					bunny2->SetReproductionPartner(bunny1);
					bunny2->SetState(GoingToReproduction::GetInstance());
				}
			}
		}
	}
}

