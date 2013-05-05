#include "Fucking.h"
#include "RestingAfterFucking.h"
#include "IBunny.h"
#include "InfectedBunny.h"
#include "HealthyBunny.h"
#include "GameProps.h"
#include <Utils/Randomizer.h>
#include <Graphics/Animation.h>
#include <assert.h>

Fucking::Fucking(void)
{
}

Fucking::~Fucking(void)
{
}

void Fucking::Enter(IBunny *bunny)
{
	InfectedBunny *ibunny = dynamic_cast<InfectedBunny*>(bunny);
	assert(ibunny != NULL);

	ibunny->m_fuckProgressTime = 0.0f;
	ibunny->m_fuckMoveCycles = 0;
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

	if (!hbunny->IsActive() || hbunny->GetState()->GetStateType() == IBunnyState::State_Dying) // make sure if bunny can be still fucked
	{
		static Randomizer random;

		ibunny->RestingAfterFuckingProgress().SetTicker(random.GetFloat(GameProps::RestingAfterTryingToFuckTimeFrom, GameProps::RestingAfterTryingToFuckTimeTo));
		ibunny->SetState(RestingAfterFucking::GetInstance());
		return;
	}

	ibunny->m_fuckProgressTime += seconds;
	if (ibunny->m_fuckMoveCycles < GameProps::FuckingHipCycles && ibunny->m_fuckProgressTime >= ibunny->m_fuckAnimEnd)
	{
		ibunny->m_fuckMoveCycles++;
		ibunny->m_fuckProgressTime = ibunny->m_fuckAnimStart;
	}

	ibunny->m_currentAnim = ibunny->m_fuckAnim;
	ibunny->m_currentAnimTime = ibunny->m_fuckProgressTime;

	ibunny->FuckingProgress().Progress(seconds);
	if (ibunny->m_currentAnimTime >= ibunny->m_fuckAnim->GetAnimLength())
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

