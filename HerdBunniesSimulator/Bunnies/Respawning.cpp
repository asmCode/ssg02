#include "Respawning.h"
#include "IBunny.h"
#include "InfectedBunny.h"
#include "BunniesManager.h"
#include "Hunting.h"
#include <assert.h>

Respawning::Respawning(void) :
	m_bunniesManager(NULL)
{
}

Respawning::~Respawning(void)
{
}

void Respawning::Initialize(BunniesManager *bunniesManager)
{
	m_bunniesManager = bunniesManager;
}

void Respawning::Enter()
{
}

void Respawning::Leave()
{
}

void Respawning::Update(IBunny *bunny, float time, float seconds)
{
	assert(bunny != NULL);

	InfectedBunny *ibunny = dynamic_cast<InfectedBunny*>(bunny);
	assert(ibunny != NULL);

	if (ibunny->IsSpawning())
		ibunny->DecreaseSpawningProcess(seconds);
	else
	{
		HealthyBunny *hbunny = m_bunniesManager->GetRandomHealthyBunny(false, true, NULL);
		if (hbunny != NULL)
		{
			ibunny->SetHuntingTarget(hbunny);
			ibunny->SetState(Hunting::GetInstance());
		}
	}
}

IBunnyState::State Respawning::GetStateType() const
{
	return IBunnyState::State_Respawning;
}

Respawning *GenericSingleton<Respawning>::instance;

