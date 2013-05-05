#include "BeeingFucked.h"
#include "HealthyBunny.h"
#include "GameProps.h"
#include "BeeingFucked.h"
#include "BunniesManager.h"
#include "Idle.h"
#include <assert.h>

BeeingFucked::BeeingFucked(void) :
	m_bunniesManager(NULL)
{
}

BeeingFucked::~BeeingFucked(void)
{
}

void BeeingFucked::Enter(IBunny *bunny)
{
}

void BeeingFucked::Leave(IBunny *bunny)
{
}

void BeeingFucked::Update(IBunny *bunny, float time, float seconds)
{
	HealthyBunny *hbunny = dynamic_cast<HealthyBunny*>(bunny);
	assert(hbunny != NULL);

	if (!hbunny->m_isAssExposed)
	{
		hbunny->m_isAssExposed = true;
		hbunny->SetMoveTarget(hbunny->m_exposeAssBaseTarget);
	}

	hbunny->m_currentAnim = hbunny->m_walkAnim;
	hbunny->m_currentAnimTime = 0.0f;

	assert(bunny != NULL);
}

IBunnyState::State BeeingFucked::GetStateType() const
{
	return IBunnyState::State_BeeingFucked;
}

void BeeingFucked::Initialize(BunniesManager *bunniesManager)
{
	assert(bunniesManager != NULL);

	m_bunniesManager = bunniesManager;
}

BeeingFucked *GenericSingleton<BeeingFucked>::instance;

