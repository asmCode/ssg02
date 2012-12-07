#include "RestingAfterFucking.h"
#include "IBunny.h"
#include "InfectedBunny.h"
#include "HealthyBunny.h"
#include "Fucking.h"
#include "GameProps.h"
#include <assert.h>

RestingAfterFucking::RestingAfterFucking(void)
{
}

RestingAfterFucking::~RestingAfterFucking(void)
{
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

	if (moveTarget.GetLength() <= 0.4f * 2)
	{
		ibunny->SetState(Fucking::GetInstance());
		hbunny->SetToBeeingFucked();
	}
	else
	{
		moveTarget.Normalize();

		ibunny->SetPosition(ibunny->GetPosition() + moveTarget * GameProps::InfectedBunnyHuntingSpeed * seconds);
	}
}

IBunnyState::State RestingAfterFucking::GetStateType() const
{
	return IBunnyState::State_RestingAfterFucking;
}

RestingAfterFucking *GenericSingleton<RestingAfterFucking>::instance;


