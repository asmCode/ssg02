#include "Hunting.h"
#include "IBunny.h"
#include "InfectedBunny.h"
#include "HealthyBunny.h"
#include "Fucking.h"
#include "RestingAfterFucking.h"
#include "GameProps.h"
#include <Utils/Randomizer.h>
#include <assert.h>

Hunting::Hunting(void)
{
}

Hunting::~Hunting(void)
{
}

void Hunting::Enter(IBunny *bunny)
{
	assert(bunny != NULL);
	InfectedBunny *ibunny = dynamic_cast<InfectedBunny*>(bunny);
	assert(ibunny != NULL);

	ibunny->DidTellToGTFO() = false;
}

void Hunting::Leave(IBunny *bunny)
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
		static Randomizer random;

		ibunny->RestingAfterFuckingProgress().SetTicker(random.GetFloat(GameProps::RestingAfterTryingToFuckTimeFrom, GameProps::RestingAfterTryingToFuckTimeTo));
		ibunny->SetState(RestingAfterFucking::GetInstance());
		return;
	}

	sm::Vec3 moveTarget = (hbunny->GetPosition() - ibunny->GetPosition());
	moveTarget.y = 0.0f;

	if (moveTarget.GetLength() <= 0.4f * 2)
	{
		ibunny->FuckingProgress().Reset();
		ibunny->SetState(Fucking::GetInstance());
		hbunny->SetToBeeingFucked();
	}
	if (moveTarget.GetLength() <= GameProps::RunningAwayDistance && !ibunny->DidTellToGTFO())
	{
		hbunny->GetTheFuckOut(ibunny);
		ibunny->DidTellToGTFO() = true;
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


