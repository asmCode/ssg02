#include "BunniesManager.h"
#include "HealthyBunny.h"
#include "Bunny.h"
#include "InfectedBunny.h"
#include "IBunnyState.h"
#include "GoingToReproduction.h"
#include "InterfaceProvider.h"
#include "GameProps.h"
#include "../BunniesView/IShapesRenderer.h"
#include <Utils/Randomizer.h>

#include <assert.h>

BunniesManager::BunniesManager() :
	m_maxHealthyBunnyIndex(0),
	m_reproduceColldown(0.0f),
	m_spawnCooldown(0.0f)
{
	for (uint32_t i = 0; i < MaxBunniesCount; i++)
		m_healthyBunnies[i] = new HealthyBunny();
	for (uint32_t i = 0; i < MaxBunniesCount; i++)
		m_infectedBunnies[i] = new InfectedBunny();
}

BunniesManager::~BunniesManager(void)
{
}

void BunniesManager::ClearBunnies()
{
	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		m_healthyBunnies[i]->Reset();
		m_infectedBunnies[i]->Reset();
	}

	m_maxHealthyBunnyIndex = 0;
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

			if (i > m_maxHealthyBunnyIndex)
				m_maxHealthyBunnyIndex = i;
		}
	}

	// TEST
	SpawnInfectedBunny();
	InfectedBunny *ib = m_infectedBunnies[0];
	assert(ib != NULL && ib->IsActive());

	ib->SetPosition(sm::Vec3(0, 0, -10));
}

void BunniesManager::BornNewRabbit(const sm::Vec3 &position)
{
	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		if (!m_healthyBunnies[i]->IsActive())
		{
			m_healthyBunnies[i]->Reset();
			m_healthyBunnies[i]->ActivateOnStart(position);
			m_healthyBunnies[i]->SetNewborn();

			if (i > m_maxHealthyBunnyIndex)
				m_maxHealthyBunnyIndex = i;

			return;
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

	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		if (m_infectedBunnies[i]->IsActive())
			m_infectedBunnies[i]->Update(time, seconds);
	}

	m_reproduceColldown += seconds;
	m_spawnCooldown += seconds;

	if (ShouldGoToReproduce())
		GoToReproduce();


	if (ShouldRespawnInfectedBunny())
		SpawnInfectedBunny();
}

void BunniesManager::Draw(float time, float seconds, const sm::Matrix &viewMatrix)
{
	IShapesRenderer *shapesRenderer = InterfaceProvider::GetShapesRenderer();

	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		if (m_healthyBunnies[i]->IsActive())
			//shapesRenderer->DrawHealthyBunny(m_healthyBunnies[i]);
			m_healthyBunnies[i]->Draw(time, seconds, viewMatrix);

		if (m_infectedBunnies[i]->IsActive())
			//shapesRenderer->DrawInfectedBunny(m_infectedBunnies[i]);
			m_infectedBunnies[i]->Draw(time, seconds, viewMatrix);
	}
}

bool BunniesManager::ShouldGoToReproduce()
{
	if (m_reproduceColldown >= GameProps::ReproductionDelay)
		return true;

	return false;
}

void BunniesManager::GoToReproduce()
{
	m_reproduceColldown = 0.0f;

	HealthyBunny *bunny1 = GetRandomHealthyBunny(true);
	HealthyBunny *bunny2 = GetRandomHealthyBunny(true, false,  bunny1);
	
	if (bunny1 != NULL && bunny2 != NULL)
	{
		bunny1->StartReproductionProcess(bunny2, true);
		bunny2->StartReproductionProcess(bunny1, false);
	}
}

HealthyBunny *BunniesManager::GetRandomHealthyBunny(bool ableToReproduce, bool ableToFuck, const IBunny *excludeFromTest)
{
	static Randomizer rand;

	int baseIndex = rand.GetInt(0, m_maxHealthyBunnyIndex);
	int index = baseIndex;

	bool firstIteration = true;

	while (true)
	{
		if (!firstIteration && index == baseIndex) // if checked all and didnt found
			return NULL;

		firstIteration = false;

		if (m_healthyBunnies[index]->IsActive() && m_healthyBunnies[index] != excludeFromTest)
		{
			bool found = true;

			if (ableToReproduce && !m_healthyBunnies[index]->CanReproduce())
				found = false;

			if (ableToFuck && !m_healthyBunnies[index]->CanBeFucked())
				found = false;

			if (found)
				return m_healthyBunnies[index];
		}

		index++;
		if (index == m_maxHealthyBunnyIndex + 1)
			index = 0;
	}
}

void BunniesManager::SpawnInfectedBunny()
{
	static Randomizer rand;

	m_spawnCooldown = 0.0f;

	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		if (!m_infectedBunnies[i]->IsActive())
		{
			m_infectedBunnies[i]->Respawn(GetRandomRespawnPosition());
			return;
		}
	}
}

sm::Vec3 BunniesManager::GetRandomRespawnPosition()
{
	static Randomizer rand;

	sm::Vec3 position;

	int side = rand.GetInt(0, 3);

	switch (side)
	{
		case 0: // left
			position = sm::Vec3(-50.0f, 0, rand.GetFloat(-50.0f, 50.0f));
			break;

		case 1: // right
			position = sm::Vec3(50.0f, 0, rand.GetFloat(-50.0f, 50.0f));
			break;

		case 2: // top
			position = sm::Vec3(rand.GetFloat(-50.0f, 50.0f), 0, 50.0f);
			break;

		case 3: // bottom
			position = sm::Vec3(rand.GetFloat(-50.0f, 50.0f), 0, -50.0f);
			break;
	}

	return position;
}

bool BunniesManager::ShouldRespawnInfectedBunny()
{
	if (m_spawnCooldown >= GameProps::RespawnDelay)
		return true;

	return false;
}

void BunniesManager::ChangeToInfected(HealthyBunny *hbunny)
{
	assert(hbunny);

	InfectedBunny *ibunny = GetUnusedInfectedBunny();
	if (ibunny == NULL)
		return;

	ibunny->ChangeFromInfected(hbunny);

	hbunny->Reset();
}

InfectedBunny* BunniesManager::GetUnusedInfectedBunny()
{
	for (uint32_t i = 0; i < MaxBunniesCount; i++)
	{
		if (!m_infectedBunnies[i]->IsActive())
			return m_infectedBunnies[i];
	}
	
	return NULL;
}

HealthyBunny** BunniesManager::GetHealthyBunnies()
{
	return m_healthyBunnies;
}

InfectedBunny** BunniesManager::GetInfectedBunnies()
{
	return m_infectedBunnies;
}

Bunny* BunniesManager::GetClosestBunny(const sm::Vec3 &position, BunnyType bunnyType, float &distance)
{
	distance = 999999999.0f;
	Bunny *closestBunny = NULL;

	if (bunnyType == BunnyType_Healthy || bunnyType == BunnyType_Any)
	{
		for (uint32_t i = 0; i < MaxBunniesCount; i++)
		{
			if (!m_healthyBunnies[i]->IsActive())
				continue;

			float currentDistance = (m_healthyBunnies[i]->GetPosition() - position).GetLength();
			if (currentDistance < distance)
			{
				distance = currentDistance;
				closestBunny = m_healthyBunnies[i];
			}
		}
	}

	if (bunnyType == BunnyType_Infected || bunnyType == BunnyType_Any)
	{
		for (uint32_t i = 0; i < MaxBunniesCount; i++)
		{
			if (!m_infectedBunnies[i]->IsActive() || m_infectedBunnies[i]->IsDying())
				continue;

			float currentDistance = (m_infectedBunnies[i]->GetPosition() - position).GetLength();
			if (currentDistance < distance)
			{
				distance = currentDistance;
				closestBunny = m_infectedBunnies[i];
			}
		}
	}

	return closestBunny;
}

