#include "HealthyBunny.h"

#include "Idle.h"
#include "SettingsInRanks.h"
#include <assert.h>
#include <stdio.h>

HealthyBunny::HealthyBunny(void) :
	m_isActive(false),
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
}

void HealthyBunny::SetState(IBunnyState *bunnyState)
{
	assert(bunnyState != NULL);

	m_bunnyState->Leave();
	m_bunnyState = bunnyState;
	m_bunnyState->Enter();
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

