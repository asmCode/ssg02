#include "Flying.h"
#include "IBunny.h"
#include "InfectedBunny.h"
#include "HealthyBunny.h"
#include "Fucking.h"
#include "RestingAfterFucking.h"
#include "GameProps.h"
#include <Utils/Randomizer.h>
#include <assert.h>

Flying::Flying(void)
{
}

Flying::~Flying(void)
{
}

void Flying::Enter(IBunny *bunny)
{
	assert(bunny != NULL);
	InfectedBunny *ibunny = dynamic_cast<InfectedBunny*>(bunny);
	assert(ibunny != NULL);
}

void Flying::Leave(IBunny *bunny)
{
}

void Flying::Update(IBunny *bunny, float time, float seconds)
{
	assert(bunny != NULL);
	InfectedBunny *ibunny = dynamic_cast<InfectedBunny*>(bunny);
	assert(ibunny != NULL);

//	ibunny->m_position += ibunny->m_flyingVector * 20.0f * seconds;
//	ibunny->m_flyingVector = (ibunny->m_flyingVector * 20.0f + sm::Vec3(0.0f, -0.5f, 0.0f)) * seconds;
//	ibunny->m_flyingVector.Normalize();

	ibunny->m_kickTrajectory.Update(seconds);
	ibunny->m_position = ibunny->m_kickTrajectory.GetPosition();

	if (ibunny->m_position.y <= 0.0f)
	{
		static Randomizer random;

		if (ibunny->m_position.x < -50.0f ||
			ibunny->m_position.x >  50.0f ||
			ibunny->m_position.z < -50.0f ||
			ibunny->m_position.z >  50.0f)
		{
			ibunny->MakeDamage(100.0f);
		}
		else
		{
			ibunny->RestingAfterFuckingProgress().SetTicker(1.0f);
			ibunny->SetState(RestingAfterFucking::GetInstance());

			ibunny->MakeDamage(50.0f);
		}
	}
}

IBunnyState::State Flying::GetStateType() const
{
	return IBunnyState::State_Flying;
}

Flying *GenericSingleton<Flying>::instance;


