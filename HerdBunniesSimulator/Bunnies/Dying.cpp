#include "Dying.h"
#include "InfectedBunny.h"
#include "GameProps.h"
#include "Dying.h"
#include "BunniesManager.h"
#include "Idle.h"
#include <assert.h>

Dying::Dying(void) :
	m_bunniesManager(NULL)
{
}

Dying::~Dying(void)
{
}

void Dying::Enter(IBunny *bunny)
{
}

void Dying::Leave(IBunny *bunny)
{
}

void Dying::Update(IBunny *bunny, float time, float seconds)
{
	assert(bunny != NULL);
	InfectedBunny *ibunny = dynamic_cast<InfectedBunny*>(bunny);
	assert(ibunny != NULL);


	sm::Matrix m_dieBodyMatrix;
	sm::Matrix m_dieHeadMatrix;
}

IBunnyState::State Dying::GetStateType() const
{
	return IBunnyState::State_Dying;
}

void Dying::Initialize(BunniesManager *bunniesManager)
{
	assert(bunniesManager != NULL);

	m_bunniesManager = bunniesManager;
}

Dying *GenericSingleton<Dying>::instance;

