#include "Idle.h"

#include "IBunny.h"
#include "HealthyBunny.h"
#include "Player.h"
#include "SettingsInRanks.h"
#include "GameProps.h"
#include <assert.h>

#include <Windows.h> // TODO wywal

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

	if (hbunny->IsBorning())
	{
		hbunny->DecreaseGrowingUpTime(seconds);
		bunny->SetPosition(bunny->GetPosition() + (hbunny->GetBorningJumpOutVector() * seconds * 3));
		return;
	}
	else if (hbunny->IsGrowingUp())
	{
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

