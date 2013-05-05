#include "Idle.h"

#include "IBunny.h"
#include "HealthyBunny.h"
#include "Player.h"
#include "SettingsInRanks.h"
#include "GameProps.h"

#include <Math/MathUtils.h>

#include <assert.h>

Idle::Idle(void) :
	m_player(NULL)
{
}

Idle::~Idle(void)
{
}

void Idle::Enter(IBunny *bunny)
{
}

void Idle::Leave(IBunny *bunny)
{
}

void Idle::Initialize(Player *player)
{
	assert(player != NULL);

	m_player = player;
}

void Idle::Update(IBunny *bunny, float time, float seconds)
{
	assert(bunny != NULL);

	HealthyBunny *hbunny = dynamic_cast<HealthyBunny*>(bunny);
	assert(hbunny != NULL);

	float growingUpCompletion = 1.0f - (hbunny->GetGrowingUpTime() / GameProps::GrowingUpTime);

	hbunny->m_useTransform = false;
	hbunny->m_mixTransform = false;
	hbunny->m_currentModel = hbunny->m_bunnyModel;

	if (hbunny->IsBorning())
	{
		hbunny->m_currentAnim = hbunny->m_babyWalkAnim;
		hbunny->m_currentAnimTime = 0.0f;
		hbunny->m_currentModel = hbunny->m_babyModel;

		static const float jumpOutDistance = 2.448 * 2.0f;

		hbunny->m_useTransform = true;

		float borningCompletion = 1.0f - ((hbunny->GetGrowingUpTime() - (GameProps::GrowingUpTime - GameProps::BorningTime))/ GameProps::BorningTime);

		float distance = jumpOutDistance * borningCompletion;

		float scaleVal = 0.5f + growingUpCompletion * 0.5f;

		sm::Matrix rotateMatrix =
			sm::Matrix::ScaleMatrix(scaleVal, scaleVal, scaleVal) *
			sm::Matrix::TranslateMatrix(0, 0.4f, 0) *
			sm::Matrix::RotateAxisMatrix(3.1415 * 4 * borningCompletion, hbunny->m_borningJumpOutAxis) *
			sm::Matrix::TranslateMatrix(0, -0.4f, 0) *
			sm::Matrix::CreateLookAt(hbunny->GetBorningJumpOutVector(), sm::Vec3(0, 1, 0));

		sm::Vec3 newPosition = bunny->GetPosition() + hbunny->GetBorningJumpOutVector() * seconds * jumpOutDistance;
		newPosition.y = 3 - 0.5f * (distance - 2.448f) * (distance - 2.448f); // distance - ((9.8f * distance * distance) / (2 * 0.707f * 7.0f * 0.707f * 7.0f));

		hbunny->m_transform =
			sm::Matrix::TranslateMatrix(newPosition) *
			rotateMatrix;

		hbunny->DecreaseGrowingUpTime(seconds);
		bunny->SetPosition(newPosition);
		return;
	}
	else if (hbunny->IsGrowingUp())
	{
		hbunny->m_currentAnim = hbunny->m_babyWalkAnim;
		hbunny->m_currentAnimTime = 0.0f;
		hbunny->m_currentModel = hbunny->m_babyModel;

		float scaleVal = 0.5f + growingUpCompletion * 0.5f;

		hbunny->m_transform =
			sm::Matrix::ScaleMatrix(scaleVal, scaleVal, scaleVal);
		hbunny->m_mixTransform = true;
		 
		bunny->SetPosition(sm::Vec3(bunny->GetPosition().x, 0, bunny->GetPosition().z));
		hbunny->DecreaseGrowingUpTime(seconds);
	}

	if (CheckSettingInRanks(bunny, time, seconds))
	{
		bunny->SetState(SettingsInRanks::GetInstance());
		return;
	}

	DoIdleStuff(bunny, time, seconds);
}

IBunnyState::State Idle::GetStateType() const
{
	return IBunnyState::State_Idle;
}

bool Idle::CheckSettingInRanks(IBunny *bunny, float time, float seconds)
{
	sm::Vec3 farmerPosition = m_player->GetPosition();
	sm::Vec3 farmerLookTarget = m_player->GetLookTarget();
	sm::Vec3 farmerMoveTarget = sm::Vec3(farmerLookTarget.x, 0.0f, farmerLookTarget.z).GetNormalized();

	sm::Vec3 bunnyPosition = bunny->GetPosition();

	sm::Vec3 farmerDirection = farmerPosition - bunnyPosition;
	sm::Vec3 farmerTarget = sm::Vec3(farmerDirection.x, 0.0f, farmerDirection.z).GetNormalized();

	if (farmerDirection.GetLength() > GameProps::HealthyBunnyDistanceToFarmer ||
		(sm::Vec3::Dot(farmerTarget.GetReversed(), farmerLookTarget) > GameProps::DangerShotAngle))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Idle::DoIdleStuff(IBunny *bunny, float time, float seconds)
{
	HealthyBunny *hbunny = dynamic_cast<HealthyBunny*>(bunny);
	assert(hbunny != NULL);

	hbunny->DecreaseRestingAfterReproductionTime(seconds);
}

Idle *GenericSingleton<Idle>::instance;

