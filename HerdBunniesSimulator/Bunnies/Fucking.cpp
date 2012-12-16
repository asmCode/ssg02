#include "Fucking.h"
#include "RestingAfterFucking.h"
#include "IBunny.h"
#include "InfectedBunny.h"
#include "HealthyBunny.h"
#include "GameProps.h"
#include <Utils/Randomizer.h>
#include <assert.h>

Fucking::Fucking(void)
{
}

Fucking::~Fucking(void)
{
}

void Fucking::Enter(IBunny *bunny)
{
}

void Fucking::Leave(IBunny *bunny)
{
}

void Fucking::Update(IBunny *bunny, float time, float seconds)
{
	assert(bunny != NULL);

	InfectedBunny *ibunny = dynamic_cast<InfectedBunny*>(bunny);
	assert(ibunny != NULL);

	HealthyBunny *hbunny = ibunny->GetHuntingTarget();
	assert(hbunny != NULL);

	ibunny->FuckingProgress().Progress(seconds);
	if (ibunny->FuckingProgress().IsTimeout())
	{
		static Randomizer random;

		ibunny->RestingAfterFuckingProgress().SetTicker(random.GetFloat(GameProps::RestingAfterFuckingTimeFrom, GameProps::RestingAfterFuckingTimeTo));
		ibunny->SetState(RestingAfterFucking::GetInstance());

		hbunny->StartChangingToInfected();
	}
}

IBunnyState::State Fucking::GetStateType() const
{
	return IBunnyState::State_Fucking;
}

Fucking *GenericSingleton<Fucking>::instance;

