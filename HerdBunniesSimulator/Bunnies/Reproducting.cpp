#include "Reproducting.h"
#include "HealthyBunny.h"
#include "GameProps.h"
#include "Reproducting.h"
#include "BunniesManager.h"
#include "Idle.h"

#include <Graphics/Animation.h>

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
	HealthyBunny *hbunny = dynamic_cast<HealthyBunny*>(bunny);
	assert(hbunny != NULL);

	hbunny->m_fuckProgressTime = 0.0f;
	hbunny->m_fuckMoveCycles = 0;
	hbunny->m_exposeAssAnimTime = 0.0f;
}

void Reproducting::Leave(IBunny *bunny)
{
}

void Reproducting::Update(IBunny *bunny, float time, float seconds)
{
	assert(bunny != NULL);

	HealthyBunny *hbunny = dynamic_cast<HealthyBunny*>(bunny);
	assert(hbunny != NULL);

	if (hbunny->m_isActiveReproducer)
	{
		hbunny->m_fuckProgressTime += seconds;
		if (hbunny->m_fuckMoveCycles < 10 && hbunny->m_fuckProgressTime >= hbunny->m_fuckAnimEnd)
		{
			hbunny->m_fuckMoveCycles++;
			hbunny->m_fuckProgressTime = hbunny->m_fuckAnimStart;
		}

		hbunny->m_currentAnim = hbunny->m_fuckAnim;
		hbunny->m_currentAnimTime = hbunny->m_fuckProgressTime;
	}
	else
	{
		hbunny->m_currentAnim = hbunny->m_walkAnim;
		hbunny->m_currentAnimTime = 0.0f;
	}

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
		// to avoid spawning new rabbit in both bunnies witch are reproducting,
		// only active reproducer can span new bunny
		if (hbunny->m_isActiveReproducer)
			m_bunniesManager->BornNewRabbit(hbunny->GetPosition());

		hbunny->m_reproductionPartner = NULL;
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

