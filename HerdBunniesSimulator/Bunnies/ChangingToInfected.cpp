#include "ChangingToInfected.h"
#include "IBunny.h"
#include "InfectedBunny.h"
#include "HealthyBunny.h"
#include "Fucking.h"
#include "BunniesManager.h"
#include "GameProps.h"
#include "Hunting.h"
#include <Utils/Randomizer.h>
#include <assert.h>

ChangingToInfected::ChangingToInfected(void)
{
}

ChangingToInfected::~ChangingToInfected(void)
{
}

void ChangingToInfected::Initialize(BunniesManager *bunniesManager)
{
	m_bunniesManager = bunniesManager;
}

void ChangingToInfected::Enter(IBunny *bunny)
{
}

void ChangingToInfected::Leave(IBunny *bunny)
{
}

void ChangingToInfected::Update(IBunny *bunny, float time, float seconds)
{
	static Randomizer rand;

	assert(bunny != NULL);

	HealthyBunny *hbunny = dynamic_cast<HealthyBunny*>(bunny);
	assert(hbunny != NULL);

	hbunny->RefreshNewTargetPosition(seconds);

	sm::Vec3 moveTarget = hbunny->GetTargetPosition() - hbunny->GetPosition();
	moveTarget.y = 0.0f;
	moveTarget.Normalize();

	hbunny->SetPosition(hbunny->GetPosition() + moveTarget * GameProps::SickBunnySpeed * seconds);

	hbunny->ChangingProgress().Progress(seconds);
	if (hbunny->ChangingProgress().IsTimeout())
	{
		m_bunniesManager->ChangeToInfected(hbunny);
	}
}

IBunnyState::State ChangingToInfected::GetStateType() const
{
	return IBunnyState::State_ChangingToInfected;
}

ChangingToInfected *GenericSingleton<ChangingToInfected>::instance;

