#include "SettingsInRanks.h"
#include "Idle.h"

#include "IBunny.h"
#include "HealthyBunny.h"
#include "Player.h"
#include "GameProps.h"
#include "BunniesManager.h"
#include <assert.h>
#include <stdio.h>

#include <Windows.h> // TODO wywal

SettingsInRanks::SettingsInRanks() :
	m_player(NULL)
{
}

SettingsInRanks::~SettingsInRanks(void)
{
}

void SettingsInRanks::Enter(IBunny *bunny)
{
	//OutputDebugStringA("SettingsInRanks enter\n");
}

void SettingsInRanks::Leave(IBunny *bunny)
{
}

void SettingsInRanks::Initialize(Player *player,
								 BunniesManager *bunniesManager)
{
	assert(player != NULL);
	assert(bunniesManager != NULL);

	m_player = player;
	m_bunniesManager = bunniesManager;
}

void SettingsInRanks::Update(IBunny *bunny, float time, float seconds)
{
	assert(bunny != NULL);

	HealthyBunny *hbunny = dynamic_cast<HealthyBunny*>(bunny);
	assert(hbunny != NULL);

	hbunny->DecreaseRestingAfterReproductionTime(seconds);

	if (hbunny->IsGrowingUp())
	{
		hbunny->DecreaseGrowingUpTime(seconds);
	}

	sm::Vec3 farmerPosition = m_player->GetPosition();
	sm::Vec3 farmerLookTarget = m_player->GetLookTarget();
	sm::Vec3 farmerMoveTarget = sm::Vec3(farmerLookTarget.x, 0.0f, farmerLookTarget.z).GetNormalized();

	sm::Vec3 bunnyPosition = bunny->GetPosition();

	sm::Vec3 farmerDirection = farmerPosition - bunnyPosition;
	sm::Vec3 farmerTarget = sm::Vec3(farmerDirection.x, 0.0f, farmerDirection.z).GetNormalized();

	sm::Vec3 bunnyMoveTarget = sm::Vec3(0, 0, 0);

	bool goingToIdleState = true;

	if (farmerDirection.GetLength() > GameProps::HealthyBunnyDistanceToFarmer)
	{
		bunnyMoveTarget = farmerTarget;

		goingToIdleState = false;

		//OutputDebugStringA("To far from farmer\n");
	}

	if (sm::Vec3::Dot(farmerTarget.GetReversed(), farmerLookTarget) > GameProps::DangerShotAngle)
	{
		sm::Vec3 runAwayTarget = sm::Vec3(farmerMoveTarget.z, 0.0f, -farmerMoveTarget.x);
		if ((farmerMoveTarget * farmerTarget.GetReversed()).y > 0.0f)
			runAwayTarget = runAwayTarget.GetReversed();
		
		bunnyMoveTarget += runAwayTarget;

		//OutputDebugStringA("In the range of fire\n");

		goingToIdleState = false;
	}

	if (goingToIdleState)
	{
		bunny->SetState(Idle::GetInstance());
	}
	else
	{
		bunnyMoveTarget.Normalize();
		sm::Vec3 newBunnyPosition = bunnyPosition + (bunnyMoveTarget * GameProps::HealthyBunnyWalkSpeed * seconds);

		if (!m_bunniesManager->CheckCollision(newBunnyPosition, 0.4f, bunny)) // TODO
			bunny->SetPosition(newBunnyPosition);
	}
}

IBunnyState::State SettingsInRanks::GetStateType() const
{
	return IBunnyState::State_SettingInRank;
}

SettingsInRanks *GenericSingleton<SettingsInRanks>::instance;

