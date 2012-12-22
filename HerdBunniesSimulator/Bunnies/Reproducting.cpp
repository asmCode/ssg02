#include "Reproducting.h"
#include "HealthyBunny.h"
#include "GameProps.h"
#include "Reproducting.h"
#include "BunniesManager.h"
#include "Idle.h"
#include <assert.h>

Reproducting::Reproducting(void) :
	m_player(NULL),
	m_bunniesManager(NULL)
{
}

Reproducting::~Reproducting(void)
{
}

void Reproducting::Enter(IBunny *bunny)
{
}

void Reproducting::Leave(IBunny *bunny)
{
}

void Reproducting::Update(IBunny *bunny, float time, float seconds)
{
	assert(bunny != NULL);

	HealthyBunny *hbunny = dynamic_cast<HealthyBunny*>(bunny);
	assert(hbunny != NULL);

	HealthyBunny *partner = hbunny->GetReproductionPartner();

	// make sure if funny can still reproduce
	if (partner == NULL ||
		!partner->IsActive() ||
		partner->GetState()->GetStateType() == IBunnyState::State_Dying)
	{
		hbunny->SetToIdle();
		return;
	}

	hbunny->SetReproductingTime(hbunny->GetReproductingTime() + seconds);

	float repTime = hbunny->GetReproductingTime();
	if (repTime > GameProps::ReproductionTime)
	{
		hbunny->SetRestingAfterReproductionTime(GameProps::RestingAfterReproduction);
		hbunny->SetReproductingTime(0.0f);
		hbunny->SetState(Idle::GetInstance());

		HealthyBunny *partner = hbunny->GetReproductionPartner();
		if (hbunny > partner)
			m_bunniesManager->BornNewRabbit(hbunny->GetPosition());

		hbunny->SetReproductionPartner(NULL);
	}
}

IBunnyState::State Reproducting::GetStateType() const
{
	return IBunnyState::State_Reproducting;
}

void Reproducting::Initialize(Player *player, BunniesManager *bunniesManager)
{
	assert(player != NULL);
	assert(bunniesManager != NULL);

	m_player = player;
	m_bunniesManager = bunniesManager;
}

Reproducting *GenericSingleton<Reproducting>::instance;

