#include "Reproducting.h"
#include "HealthyBunny.h"
#include "GameProps.h"
#include "Reproducting.h"
#include "Idle.h"
#include <assert.h>

Reproducting::Reproducting(void) :
	m_player(NULL)
{
}

Reproducting::~Reproducting(void)
{
}

void Reproducting::Enter()
{
}

void Reproducting::Leave()
{
}

void Reproducting::Update(IBunny *bunny, float time, float seconds)
{
	assert(bunny != NULL);

	HealthyBunny *hbunny = dynamic_cast<HealthyBunny*>(bunny);
	assert(hbunny != NULL);

	hbunny->SetReproductingTime(hbunny->GetReproductingTime() + seconds);

	float repTime = hbunny->GetReproductingTime();
	if (repTime > GameProps::ReproductionTime)
	{
		hbunny->SetRestingAfterReproductionTime(GameProps::RestingAfterReproduction);
		hbunny->SetReproductingTime(0.0f);
		hbunny->SetState(Idle::GetInstance());
	}
}

IBunnyState::State Reproducting::GetStateType() const
{
	return IBunnyState::State_Reproducting;
}

Reproducting *GenericSingleton<Reproducting>::instance;

