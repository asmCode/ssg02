#include "RestingAfterFucking.h"
#include "IBunny.h"
#include "InfectedBunny.h"
#include "HealthyBunny.h"
#include "Fucking.h"
#include "BunniesManager.h"
#include "GameProps.h"
#include "Hunting.h"
#include <Utils/Randomizer.h>
#include <assert.h>

RestingAfterFucking::RestingAfterFucking(void)
{
}

RestingAfterFucking::~RestingAfterFucking(void)
{
}

void RestingAfterFucking::Initialize(BunniesManager *bunniesManager)
{
	m_bunniesManager = bunniesManager;
}

void RestingAfterFucking::Enter(IBunny *bunny)
{
	dynamic_cast<InfectedBunny*>(bunny)->m_targetPositionRefreshColldown = 0.0f;
}

void RestingAfterFucking::Leave(IBunny *bunny)
{
}

void RestingAfterFucking::Update(IBunny *bunny, float time, float seconds)
{
	static Randomizer rand;

	assert(bunny != NULL);

	InfectedBunny *ibunny = dynamic_cast<InfectedBunny*>(bunny);
	assert(ibunny != NULL);

	ibunny->m_currentAnim = ibunny->m_walkAnim;
	ibunny->RefreshNewTargetPosition(seconds);
	ibunny->UpdateMovement(seconds, GameProps::InfectedBunnyRestingSpeed, GameProps::DelayBetweenWalkJump);

	ibunny->RestingAfterFuckingProgress().Progress(seconds);
	if (ibunny->RestingAfterFuckingProgress().IsTimeout())
	{
		HealthyBunny *hbunny = m_bunniesManager->GetRandomHealthyBunny(false, true, NULL);
		if (hbunny != NULL)
		{
			ibunny->SetHuntingTarget(hbunny);
			ibunny->SetState(Hunting::GetInstance());
		}
	}
}

IBunnyState::State RestingAfterFucking::GetStateType() const
{
	return IBunnyState::State_RestingAfterFucking;
}

RestingAfterFucking *GenericSingleton<RestingAfterFucking>::instance;

