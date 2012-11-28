#include "Hunting.h"
#include "IBunny.h"
#include "InfectedBunny.h"
#include "HealthyBunny.h"
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

	sm::Vec3 moveTarget = (hbunny->GetPosition() - ibunny->GetPosition());
	moveTarget.y = 0.0f;
	moveTarget.Normalize();

	ibunny->SetPosition(ibunny->GetPosition() + moveTarget * GameProps::InfectedBunnyHuntingSpeed * seconds);
}

IBunnyState::State Hunting::GetStateType() const
{
	return IBunnyState::State_Hunting;
}

Hunting *GenericSingleton<Hunting>::instance;


