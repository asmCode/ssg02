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

