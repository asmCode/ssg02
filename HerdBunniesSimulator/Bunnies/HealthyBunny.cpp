#include "HealthyBunny.h"

#include "Idle.h"
#include "SettingsInRanks.h"
#include "GameProps.h"
#include <Utils/Randomizer.h>
#include <assert.h>
#include <stdio.h>

HealthyBunny::HealthyBunny(void) :
	m_isActive(false),
	m_reproductionPartner(NULL),
	m_reproductingTime(0.0f),
	m_restingAfterReproduction(0.0f),
	m_growingUpTime(0.0f),
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
	m_reproductionPartner = NULL;
	m_reproductingTime = 0.0f;
	m_restingAfterReproduction = 0.0f;
	m_growingUpTime = 0.0f;
	SetState(SettingsInRanks::GetInstance());
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

	if (m_bunnyState != NULL)
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

void HealthyBunny::SetNewborn()
{
	m_growingUpTime = GameProps::GrowingUpTime;

	static Randomizer rand;

	m_borningJumpOutVector = sm::Vec3(rand.GetFloat(-1.0f, 1.0), 0.0f, rand.GetFloat(-1.0f, 1.0f));
	m_borningJumpOutVector.Normalize();

	SetState(Idle::GetInstance());
}

bool HealthyBunny::IsBorning() const
{
	return m_growingUpTime > (GameProps::GrowingUpTime - GameProps::BorningTime);
}

bool HealthyBunny::IsGrowingUp() const
{
	return m_growingUpTime > 0.0f;
}

float HealthyBunny::GetGrowingUpTime() const
{
	return m_growingUpTime;
}

void HealthyBunny::DecreaseGrowingUpTime(float seconds)
{
	m_growingUpTime -= seconds;
	if (m_growingUpTime < 0.0f)
		m_growingUpTime = 0.0f;
}

const sm::Vec3 &HealthyBunny::GetBorningJumpOutVector() const
{
	return m_borningJumpOutVector;
}

bool HealthyBunny::CanReproduce() const
{
	if ((m_bunnyState->GetStateType() == IBunnyState::State_Idle || 
		m_bunnyState->GetStateType() == IBunnyState::State_SettingInRank) &&
		m_restingAfterReproduction == 0.0f &&
		!IsBorning() &&
		!IsGrowingUp())
		return true;

	return false;
}

bool HealthyBunny::CanBeFucked() const
{
	return
		!IsBorning() &&
		!IsGrowingUp() &&
		(m_bunnyState->GetStateType() == IBunnyState::State_Idle || 
		m_bunnyState->GetStateType() == IBunnyState::State_SettingInRank ||
		m_bunnyState->GetStateType() == IBunnyState::State_GoingToReproduction ||
		m_bunnyState->GetStateType() == IBunnyState::State_RunningAway);
}

void HealthyBunny::GetTheFuckOut()
{
	// zmien stan na spierdalanie
}

void HealthyBunny::SetToBeeingFucked()
{
	// zmien stan na beeing fucked
}

