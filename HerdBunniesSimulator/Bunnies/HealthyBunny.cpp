#include "HealthyBunny.h"

#include "Idle.h"
#include "SettingsInRanks.h"
#include <assert.h>
#include <stdio.h>

HealthyBunny::HealthyBunny(void) :
	m_isActive(false),
	m_reproductionPartner(NULL),
	m_reproductingTime(0.0f),
	m_restingAfterReproduction(0.0f),
	m_bunnyState(SettingsInRanks::GetInstance())
{
}

HealthyBunny::~HealthyBunny(void)
{
}

void HealthyBunny::Update(float time, float seconds)
{
	assert(m_bunnyState != NULL);

	m_bunnyState->Update(this, time, seconds);
}

void HealthyBunny::Reset()
{
	m_isActive = false;
	m_position = sm::Vec3(0, 0, 0);
	m_moveTarget = sm::Vec3(0, 0, -1);
}

bool HealthyBunny::IsActive() const
{
	return m_isActive;
}

void HealthyBunny::ActivateOnStart(const sm::Vec3 &position)
{
	m_isActive = true;
	m_position = position;
	m_reproductionPartner = NULL;
}

void HealthyBunny::SetState(IBunnyState *bunnyState)
{
	assert(bunnyState != NULL);

	m_bunnyState->Leave();
	m_bunnyState = bunnyState;
	m_bunnyState->Enter();
}

const IBunnyState *HealthyBunny::GetState() const
{
	assert(m_bunnyState != NULL);

	return m_bunnyState;
}

void HealthyBunny::SetPosition(const sm::Vec3 &position)
{
	m_position = position;
}

void HealthyBunny::SetMoveTarget(const sm::Vec3 &moveTarget)
{
	m_moveTarget = moveTarget;
}

const sm::Vec3 HealthyBunny::GetPosition() const
{
	return m_position;
}

const sm::Vec3 HealthyBunny::GetMoveTarget() const
{
	return m_moveTarget;
}

void HealthyBunny::SetReproductionPartner(HealthyBunny *bunny)
{
	m_reproductionPartner = bunny;
}

HealthyBunny *HealthyBunny::GetReproductionPartner()
{
	return m_reproductionPartner;
}

void HealthyBunny::SetReproductingTime(float time)
{
	m_reproductingTime = time;
}

float HealthyBunny::GetReproductingTime() const
{
	return m_reproductingTime;
}

void HealthyBunny::SetRestingAfterReproductionTime(float time)
{
	m_restingAfterReproduction = time;
}

void HealthyBunny::DecreaseRestingAfterReproductionTime(float seconds)
{
	m_restingAfterReproduction -= seconds;
	if (m_restingAfterReproduction < 0.0f)
		m_restingAfterReproduction = 0.0f;
}

bool HealthyBunny::CanReproduce() const
{
	if ((m_bunnyState->GetStateType() == IBunnyState::State_Idle || 
		m_bunnyState->GetStateType() == IBunnyState::State_SettingInRank) &&
		m_restingAfterReproduction == 0.0f)
		return true;

	return false;
}