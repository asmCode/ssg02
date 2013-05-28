#include "GameScreen.h"

#include "Player.h"
#include "IGun.h"
#include "IBullet.h"
#include "Shotgun.h"
#include "BunniesManager.h"
#include "HealthyBunny.h"
#include "InfectedBunny.h"
#include "Idle.h"
#include "SettingsInRanks.h"
#include "Reproducting.h"
#include "ChangingToInfected.h"
#include "Respawning.h"
#include "RestingAfterFucking.h"
#include "BeeingFucked.h"
#include "Shotgun.h"
#include "InterfaceProvider.h"
#include "Environment.h"
#include "Ground.h"
#include "LevelEnvironment.h"
#include "Skydome.h"
#include "GameProps.h"

#include "../BunniesView/IShapesRenderer.h"
#include "../BunniesView/WinShapesRenderer.h"

#include <Graphics/Shader.h>
#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/MeshPart.h>
#include <Graphics/Texture.h>
#include <Graphics/Content/Content.h>

GameScreen::GameScreen(void) :
	m_player(NULL),
	m_bunniesMgr(NULL),
	m_activeGun(NULL)
{
}

GameScreen::~GameScreen(void)
{
}

bool GameScreen::Initialize()
{
	m_player = new Player();
	m_bunniesMgr = new BunniesManager();
	m_bunniesMgr->ResetForNewGame(8);

	Shotgun *shotgun = new Shotgun(m_player);
	m_activeGun = shotgun;

	m_ground = new Ground();
	m_levelEnv = new LevelEnvironment();
	m_skydome = new Skydome();

	Idle::GetInstance()->Initialize(m_player);
	SettingsInRanks::GetInstance()->Initialize(m_player, m_bunniesMgr);
	Reproducting::GetInstance()->Initialize(m_player, m_bunniesMgr);
	Respawning::GetInstance()->Initialize(m_bunniesMgr);
	RestingAfterFucking::GetInstance()->Initialize(m_bunniesMgr);
	BeeingFucked::GetInstance()->Initialize(m_bunniesMgr);
	ChangingToInfected::GetInstance()->Initialize(m_bunniesMgr);

	uint32_t screenWidth = Environment::GetInstance()->GetScreenWidth();
	uint32_t screenHeight = Environment::GetInstance()->GetScreenHeight();
	m_projMatrix = sm::Matrix::PerspectiveMatrix(45.0f, static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 1000.0f);

	return true;
}

bool GameScreen::InitResources()
{
	return false;
}

bool GameScreen::ReleaseResources()
{
	return false;
}

void GameScreen::Draw(float time, float seconds)
{
	m_skydome->Draw(time, seconds);
	m_ground->Draw(time, seconds);
	m_levelEnv->Draw(time, seconds);
	m_bunniesMgr->Draw(time, seconds, m_player->GetViewMatrix());
	m_activeGun->Draw(time, seconds);
	m_player->Draw(time, seconds);

	float width = Environment::GetInstance()->GetScreenWidth();
	float height = Environment::GetInstance()->GetScreenHeight();
}

void GameScreen::Update(float time, float seconds)
{
	m_player->Update(time, seconds);
	sm::Matrix viewMatrix = m_player->GetViewMatrix();

	m_skydome->SetViewMatrix(viewMatrix);
	m_skydome->SetProjMatrix(m_projMatrix);
	m_skydome->Update(time, seconds);

	m_ground->SetViewMatrix(viewMatrix);
	m_ground->Update(time, seconds);

	m_levelEnv->SetViewMatrix(viewMatrix);
	m_levelEnv->Update(time, seconds);

	m_activeGun->Update(time, seconds);
	IBullet *bullet = m_activeGun->GetBullet();
	if (bullet != NULL)
	{
		bullet->TakeDamage(this);
	}

	m_bunniesMgr->Update(time, seconds);

	float distance = 0;
	Bunny *bunny = m_bunniesMgr->GetClosestBunny(m_player->GetPosition(), BunnyType_Infected, distance);
	if (bunny != NULL &&
		distance <= GameProps::KickMaxDistance &&
		distance >= GameProps::KickMinDistance &&
		m_player->IsAbleToKick())
	{
		sm::Vec3 bunnyPosition(bunny->GetPosition().x, 0, bunny->GetPosition().z);
		sm::Vec3 playerPosition(m_player->GetPosition().x, 0, m_player->GetPosition().z);
		sm::Vec3 playerTarget(m_player->GetLookTarget().x, 0.0f, m_player->GetLookTarget().z);
		playerTarget.Normalize();

		sm::Vec3 bunnyDirection = (bunnyPosition - playerPosition).GetNormalized();
		if (sm::Vec3::Dot(playerTarget, bunnyDirection) >= GameProps::KickFOV)
			m_player->Kick();
	}
}

void GameScreen::HandlePress(uint32_t pointIndex, const sm::Vec2 &point)
{
	m_activeGun->PullTrigger();
}

void GameScreen::HandleRelease(uint32_t pointIndex, const sm::Vec2 &point)
{
	m_activeGun->ReleaseTrigger();
}

void GameScreen::HandleMove(uint32_t pointIndex, const sm::Vec2 &point)
{
}

Player* GameScreen::GetPlayer()
{
	return m_player;
}

void GameScreen::GetAllDamageables(IDamageable **objects, uint32_t &count)
{
	count = 0;

	uint32_t index = 0;

	HealthyBunny **healthyBunnies = m_bunniesMgr->GetHealthyBunnies();
	InfectedBunny **infectedBunnies = m_bunniesMgr->GetInfectedBunnies();

	sm::Vec3 bunnyDirection;

	for (uint32_t i = 0; i < BunniesManager::MaxBunniesCount; i++)
	{
		if (healthyBunnies[i]->IsActive())
		{
			objects[index] = healthyBunnies[i];
			index++;
		}

		if (infectedBunnies[i]->IsActive())
		{
			objects[index] = infectedBunnies[i];
			index++;
		}
	}

	count = index;
}

void GameScreen::GetDamageablesInCone(
	IDamageable **objects,
	uint32_t &count,
	const sm::Vec3 &coneTop,
	const sm::Vec3 &coneTarget,
	float cosOfAngle)
{
	count = 0;

	uint32_t index = 0;

	HealthyBunny **healthyBunnies = m_bunniesMgr->GetHealthyBunnies();
	InfectedBunny **infectedBunnies = m_bunniesMgr->GetInfectedBunnies();

	sm::Vec3 bunnyDirection;

	for (uint32_t i = 0; i < BunniesManager::MaxBunniesCount; i++)
	{
		if (healthyBunnies[i]->IsActive())
		{
			bunnyDirection = (healthyBunnies[i]->GetPosition() - coneTop).GetNormalized();
			if (sm::Vec3::Dot(coneTarget, bunnyDirection) >= cosOfAngle)
			{
				objects[index] = healthyBunnies[i];
				index++;
			}
		}

		if (infectedBunnies[i]->IsActive())
		{
			bunnyDirection = (infectedBunnies[i]->GetPosition() - coneTop).GetNormalized();
			if (sm::Vec3::Dot(coneTarget, bunnyDirection) >= cosOfAngle)
			{
				objects[index] = infectedBunnies[i];
				index++;
			}
		}
	}

	count = index;
}

void GameScreen::GetDamageablesInRange(
	IDamageable **objects,
	uint32_t &count,
	const sm::Vec3 &position,
	float range)
{
}

