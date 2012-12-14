#include "RestingAfterFucking.h"
#include "IBunny.h"
#include "InfectedBunny.h"
#include "HealthyBunny.h"
#include "Fucking.h"
#include "BunniesManager.h"
#include "GameProps.h"
#include "Hunting.h"
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

void RestingAfterFucking::Enter()
{
}

void RestingAfterFucking::Leave()
{
}

void RestingAfterFucking::Update(IBunny *bunny, float time, float seconds)
{
	assert(bunny != NULL);

	InfectedBunny *ibunny = dynamic_cast<InfectedBunny*>(bunny);
	assert(ibunny != NULL);

	ibunny->RefreshNewTargetPosition(seconds);

	sm::Vec3 moveTarget = ibunny->GetTargetPosition() - ibunny->GetPosition();
	moveTarget.y = 0.0f;
	moveTarget.Normalize();

	ibunny->SetPosition(ibunny->GetPosition() + moveTarget * GameProps::InfectedBunnyRestingSpeed * seconds);

	ibunny->RestingAfterFuckingProgress() += seconds;
	if (ibunny->RestingAfterFuckingProgress() >= GameProps::RestingAfterFuckingTime)
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

