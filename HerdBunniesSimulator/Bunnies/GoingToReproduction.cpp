#include "GoingToReproduction.h"
#include "HealthyBunny.h"
#include "GameProps.h"
#include "Reproducting.h"
#include <assert.h>

GoingToReproduction::GoingToReproduction(void) :
	m_player(NULL)
{
}

GoingToReproduction::~GoingToReproduction(void)
{
}

void GoingToReproduction::Enter(IBunny *bunny)
{
}

void GoingToReproduction::Leave(IBunny *bunny)
{
}

void GoingToReproduction::Update(IBunny *bunny, float time, float seconds)
{
	assert(bunny != NULL);

	HealthyBunny *hbunny = dynamic_cast<HealthyBunny*>(bunny);
	assert(hbunny != NULL);

	HealthyBunny *partner = hbunny->GetReproductionPartner();
	assert(partner != NULL);

	// make sure if funny can still reproduce
	if ((partner->GetState()->GetStateType() != IBunnyState::State_GoingToReproduction &&
		partner->GetState()->GetStateType() != IBunnyState::State_Reproducting) ||
		partner->GetReproductionPartner() != hbunny ||
		partner->GetState()->GetStateType() == IBunnyState::State_Dying)
	{
		hbunny->SetToIdle();
		return;
	}

	sm::Vec3 moveTarget = partner->GetPosition() - hbunny->GetPosition();
	moveTarget.y = 0;
	moveTarget.Normalize();

	sm::Vec3 newBunnyPosition = hbunny->GetPosition() + (moveTarget * GameProps::HealthyBunnyWalkSpeed * seconds);
	hbunny->SetPosition(newBunnyPosition);

	if ((hbunny->GetPosition() - partner->GetPosition()).GetLength() < (0.4f * 2)) // TODO
		hbunny->SetState(Reproducting::GetInstance());
}

IBunnyState::State GoingToReproduction::GetStateType() const
{
	return IBunnyState::State_GoingToReproduction;
}

GoingToReproduction *GenericSingleton<GoingToReproduction>::instance;

