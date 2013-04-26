#include "GoingToReproduction.h"
#include "HealthyBunny.h"
#include "GameProps.h"
#include "Reproducting.h"

#include <Graphics/Animation.h>

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
	HealthyBunny *hbunny = dynamic_cast<HealthyBunny*>(bunny);
	assert(hbunny != NULL);

	hbunny->m_isAssExposed = false;
	hbunny->m_exposeAssAnimTime = 0.0f;
	hbunny->	m_exposeAssAngleDiff = 0.0f;
	hbunny->m_exposeAssAxis.Set(0.0f, 0.0f, 0.0f);
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

	if ((hbunny->m_isActiveReproducer || (!hbunny->m_isActiveReproducer && hbunny->m_isAssExposed)) &&
		(hbunny->GetPosition() - partner->GetPosition()).GetLength() < (0.5f * 2)) // TODO
	{
		hbunny->SetState(Reproducting::GetInstance());
	}
	else if (!hbunny->m_isActiveReproducer &&
			(hbunny->GetPosition() - partner->GetPosition()).GetLength() < (2.0f * 2)) // TODO
	{
		if (hbunny->m_exposeAssAxis == sm::Vec3(0, 0, 0))
		{
			hbunny->m_exposeAssAxis = partner->GetMoveTarget() * hbunny->GetMoveTarget();
			hbunny->m_exposeAssAngleDiff = sm::Vec3::GetAngle(partner->GetMoveTarget(), hbunny->GetMoveTarget());
			hbunny->m_exposeAssBaseTarget = hbunny->GetMoveTarget();
		}
		else
		{
			hbunny->m_exposeAssAnimTime += seconds;

			float walkAnimLength = hbunny->m_walkAnim->GetAnimLength();

			if (hbunny->m_exposeAssAnimTime >= walkAnimLength)
			{
				hbunny->m_exposeAssAnimTime = walkAnimLength;
				hbunny->m_isAssExposed = true;
			}

			if (hbunny->m_exposeAssAnimTime < walkAnimLength)
			{
				float rotAngle = (hbunny->m_exposeAssAnimTime / walkAnimLength) * hbunny->m_exposeAssAngleDiff;
				sm::Matrix rot = sm::Matrix::RotateAxisMatrix(rotAngle, hbunny->m_exposeAssAxis);
				hbunny->SetMoveTarget(rot * hbunny->m_exposeAssBaseTarget);
			}

			hbunny->m_currentAnim = hbunny->m_walkAnim;
			hbunny->m_currentAnimTime = hbunny->m_exposeAssAnimTime;
		}
	}
	else
	{
		hbunny->SetDestinationPosition(partner->GetPosition());
		hbunny->UpdateMovement(seconds, GameProps::HealthyBunnyWalkSpeed, GameProps::DelayBetweenWalkJump);
	}
}

IBunnyState::State GoingToReproduction::GetStateType() const
{
	return IBunnyState::State_GoingToReproduction;
}

GoingToReproduction *GenericSingleton<GoingToReproduction>::instance;

