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

	ibunny->m_dieBodyTrajectory.Update(seconds);
	ibunny->m_dieHeadTrajectory.Update(seconds);

	sm::Matrix bodyRot = sm::Matrix::RotateAxisMatrix(ibunny->m_dieBodyAngleProgress * ibunny->m_dieBodyAngleSpeed, ibunny->m_dieBodyAxis);
	sm::Matrix headRot = sm::Matrix::RotateAxisMatrix(ibunny->m_dieHeadAngleProgress * ibunny->m_dieHeadAngleSpeed, ibunny->m_dieHeadAxis);

	ibunny->m_dieBodyAngleProgress += seconds;
	ibunny->m_dieHeadAngleProgress += seconds;

	ibunny->m_dieBodyMatrix = sm::Matrix::TranslateMatrix(ibunny->m_dieBodyTrajectory.GetPosition()) * bodyRot * ibunny->m_dieBaseMatrix;
	ibunny->m_dieHeadMatrix = sm::Matrix::TranslateMatrix(ibunny->m_dieHeadTrajectory.GetPosition()) * headRot * ibunny->m_dieBaseMatrix;

	if (ibunny->m_dieBodyTrajectory.GetPosition().y < 2.0f &&
		ibunny->m_dieHeadTrajectory.GetPosition().y < -2.0f)
	{
		ibunny->Reset(); // remove from level
	}
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

