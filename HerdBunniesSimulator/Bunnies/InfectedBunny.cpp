#include "InfectedBunny.h"
#include "IBunnyState.h"
#include "HealthyBunny.h"
#include "Respawning.h"
#include "Dying.h"
#include "RestingAfterFucking.h"
#include "GameProps.h"
#include <Utils/Randomizer.h>
#include <stddef.h>
#include <assert.h>

InfectedBunny::InfectedBunny() :
	m_isActive(false),
	m_spawningProgress(0.0f),
	m_huntingTarget(NULL),
	m_bunnyState(NULL),
	m_targetPositionRefreshColldown(0.0f),
	m_fuckingProgress(GameProps::FuckingTime)
{
}

InfectedBunny::~InfectedBunny(void)
{
}

bool InfectedBunny::IsActive() const
{
	return m_isActive;
}

void InfectedBunny::SetState(IBunnyState *bunnyState)
{
	assert(bunnyState != NULL);

	if (m_bunnyState != NULL)
		m_bunnyState->Leave(this);
	m_bunnyState = bunnyState;
	m_bunnyState->Enter(this);
}

const IBunnyState *InfectedBunny::GetState() const
{
	assert(m_bunnyState != NULL);

	return m_bunnyState;
}

void InfectedBunny::SetPosition(const sm::Vec3 &position)
{
	m_position = position;
}

void InfectedBunny::SetMoveTarget(const sm::Vec3 &moveTarget)
{
	m_moveTarget = moveTarget;
}

const sm::Vec3 InfectedBunny::GetPosition() const
{
	return m_position;
}

const sm::Vec3 InfectedBunny::GetMoveTarget() const
{
	return m_moveTarget;
}

void InfectedBunny::Update(float time, float seconds)
{
	assert(m_bunnyState != NULL);

	m_bunnyState->Update(this, time, seconds);
}

void InfectedBunny::Respawn(const sm::Vec3 &position)
{
	m_isActive = true;
	m_spawningProgress = GameProps::SpawningTime;
	SetPosition(position);
	SetState(Respawning::GetInstance());
}

void InfectedBunny::Reset()
{
	m_isActive = false;	
	m_huntingTarget = NULL;
	m_targetPositionRefreshColldown = 0.0f;
}

float InfectedBunny::IsSpawning() const
{
	return m_spawningProgress > 0.0f;
}

void InfectedBunny::DecreaseSpawningProcess(float seconds)
{
	m_spawningProgress -= seconds;
	if (m_spawningProgress < 0.0f)
		m_spawningProgress = 0.0f;
}

void InfectedBunny::SetHuntingTarget(HealthyBunny *healthyBunny)
{
	m_huntingTarget = healthyBunny;
}

HealthyBunny *InfectedBunny::GetHuntingTarget()
{
	return m_huntingTarget;
}

const sm::Vec3& InfectedBunny::GetTargetPosition() const
{
	return m_targetPosition;
}

void InfectedBunny::SetTargetPosition(const sm::Vec3 &targetPosition)
{
	m_targetPosition = targetPosition;
}

void InfectedBunny::RefreshNewTargetPosition(float seconds)
{
	static Randomizer random;

	float distance = (m_targetPosition - m_position).GetLength();

	m_targetPositionRefreshColldown -= seconds;
	if (m_targetPositionRefreshColldown <= 0.0f || distance <= 0.4f)
	{
		m_targetPositionRefreshColldown = random.GetFloat(
			GameProps::RefreshNewTargetPositionFrom,
			GameProps::RefreshNewTargetPositionTo);

		m_targetPosition.x = random.GetFloat(-50.0f, 50.0f);
		m_targetPosition.y = 0.0f;
		m_targetPosition.z = random.GetFloat(-50.0f, 50.0f);
	}
}

Ticker& InfectedBunny::FuckingProgress()
{
	return m_fuckingProgress;
}

Ticker& InfectedBunny::RestingAfterFuckingProgress()
{
	return m_restingAfterFuckingProgress;
}

bool& InfectedBunny::DidTellToGTFO()
{
	return m_didTellToGTFO;
}

void InfectedBunny::ChangeFromInfected(HealthyBunny *hbunny)
{
	assert(hbunny != NULL);

	m_isActive = true;
	SetPosition(hbunny->GetPosition());
	SetMoveTarget(hbunny->GetMoveTarget());
	m_restingAfterFuckingProgress.SetTicker(GameProps::RestingAfterChangedToInfectedTime);
	SetState(RestingAfterFucking::GetInstance());
}

void InfectedBunny::MakeDamage(float damageValue)
{
	m_health -= damageValue;
	if (m_health < 0.0f)
		m_health = 0.0f;

	if (m_health == 0.0f)
	{
		Die();
	}
}

void InfectedBunny::Die()
{
	SetState(Dying::GetInstance());
}

