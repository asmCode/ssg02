#include "Hunting.h"
#include "IBunny.h"
#include "InfectedBunny.h"
#include "HealthyBunny.h"
#include "Fucking.h"
#include "RestingAfterFucking.h"
#include "GameProps.h"
#include <assert.h>

Hunting::Hunting(void)
{
}

Hunting::~Hunting(void)
{
}

void Hunting::Enter()
{
}

void Hunting::Leave()
{
}

void Hunting::Update(IBunny *bunny, float time, float seconds)
{
	assert(bunny != NULL);

	InfectedBunny *ibunny = dynamic_cast<InfectedBunny*>(bunny);
	assert(ibunny != NULL);

	HealthyBunny *hbunny = ibunny->GetHuntingTarget();
	assert(hbunny != NULL);

	if (!hbunny->CanBeFucked()) // make sure if bunny can be still fucked
	{
		ibunny->RestingAfterFuckingProgress() = GameProps::RestingAfterFuckingTime / 2.0f; // TODO: czas dwa razy mniejszy niz zwykle
		ibunny->SetState(RestingAfterFucking::GetInstance());
	}

	sm::Vec3 moveTarget = (hbunny->GetPosition() - ibunny->GetPosition());
	moveTarget.y = 0.0f;

	if (moveTarget.GetLength() <= 0.4f * 2)
	{
		ibunny->FuckingProgress() = 0.0f;
		ibunny->SetState(Fucking::GetInstance());
		hbunny->SetToBeeingFucked();
	}
	else
	{
		moveTarget.Normalize();

		ibunny->SetPosition(ibunny->GetPosition() + moveTarget * GameProps::InfectedBunnyHuntingSpeed * seconds);
	}
}

IBunnyState::State Hunting::GetStateType() const
{
	return IBunnyState::State_Hunting;
}

Hunting *GenericSingleton<Hunting>::instance;


