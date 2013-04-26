#include "RunningAway.h"
#include "IBunny.h"
#include "InfectedBunny.h"
#include "HealthyBunny.h"
#include "BunniesManager.h"
#include "GameProps.h"
#include <assert.h>

RunningAway::RunningAway(void)
{
}

RunningAway::~RunningAway(void)
{
}

void RunningAway::Initialize(BunniesManager *bunniesManager)
{
	m_bunniesManager = bunniesManager;
}

void RunningAway::Enter(IBunny *bunny)
{
}

void RunningAway::Leave(IBunny *bunny)
{
}

void RunningAway::Update(IBunny *bunny, float time, float seconds)
{
	assert(bunny != NULL);

	HealthyBunny *hbunny = dynamic_cast<HealthyBunny*>(bunny);
	assert(hbunny != NULL);
	
	hbunny->RefreshNewTargetPosition(seconds);

	/*sm::Vec3 moveTarget = hbunny->GetTargetPosition() - hbunny->GetPosition();
	moveTarget.y = 0.0f;
	moveTarget.Normalize();

	hbunny->SetPosition(hbunny->GetPosition() + moveTarget * GameProps::HealthyBunnyRunSpeed * seconds);*/

	hbunny->m_currentAnim = hbunny->m_runAnim;
	hbunny->SetDestinationPosition(hbunny->GetTargetPosition());
	hbunny->UpdateMovement(seconds, GameProps::HealthyBunnyRunSpeed, GameProps::DelayBetweenRunJump);
}

IBunnyState::State RunningAway::GetStateType() const
{
	return IBunnyState::State_RunningAway;
}

RunningAway *GenericSingleton<RunningAway>::instance;

