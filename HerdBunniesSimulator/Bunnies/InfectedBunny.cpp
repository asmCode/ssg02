#include "InfectedBunny.h"
#include "IBunnyState.h"
#include "HealthyBunny.h"
#include "Respawning.h"
#include "GameProps.h"
#include <stddef.h>
#include <assert.h>

InfectedBunny::InfectedBunny() :
	m_isActive(false),
	m_spawningProgress(0.0f),
	m_huntingTarget(NULL),
	m_bunnyState(NULL)
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
		m_bunnyState->Leave();
	m_bunnyState = bunnyState;
	m_bunnyState->Enter();
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

