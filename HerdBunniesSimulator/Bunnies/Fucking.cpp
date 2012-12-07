#include "Fucking.h"
#include "IBunny.h"
#include "InfectedBunny.h"
#include "HealthyBunny.h"
#include "GameProps.h"
#include <assert.h>

Fucking::Fucking(void)
{
}

Fucking::~Fucking(void)
{
}

void Fucking::Enter()
{
}

void Fucking::Leave()
{
}

void Fucking::Update(IBunny *bunny, float time, float seconds)
{
	assert(bunny != NULL);

	InfectedBunny *ibunny = dynamic_cast<InfectedBunny*>(bunny);
	assert(ibunny != NULL);

	HealthyBunny *hbunny = ibunny->GetHuntingTarget();
	assert(hbunny != NULL);
}

IBunnyState::State Fucking::GetStateType() const
{
	return IBunnyState::State_Fucking;
}

Fucking *GenericSingleton<Fucking>::instance;

