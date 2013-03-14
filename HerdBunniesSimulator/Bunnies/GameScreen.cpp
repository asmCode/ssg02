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
#include <Windows.h>

#include "../BunniesView/IShapesRenderer.h"
#include "../BunniesView/WinShapesRenderer.h"

#include <Graphics/Shader.h>
#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/MeshPart.h>
#include <Graphics/Content/Content.h>

Model *model;
Shader *shader;

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
	model = InterfaceProvider::GetContent()->Get<Model>("cube");
	shader = InterfaceProvider::GetContent()->Get<Shader>("CelShading");
	shader->BindVertexChannel(0, "a_position");
	shader->BindVertexChannel(1, "a_normal");
	shader->BindVertexChannel(2, "a_coords");
	shader->LinkProgram();

	m_player = new Player();
	m_bunniesMgr = new BunniesManager();
	m_bunniesMgr->ResetForNewGame(4);

	Shotgun *shotgun = new Shotgun(m_player);
	m_activeGun = shotgun;

	Idle::GetInstance()->Initialize(m_player);
	SettingsInRanks::GetInstance()->Initialize(m_player, m_bunniesMgr);
	Reproducting::GetInstance()->Initialize(m_player, m_bunniesMgr);
	Respawning::GetInstance()->Initialize(m_bunniesMgr);
	RestingAfterFucking::GetInstance()->Initialize(m_bunniesMgr);
	BeeingFucked::GetInstance()->Initialize(m_bunniesMgr);
	ChangingToInfected::GetInstance()->Initialize(m_bunniesMgr);

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
	/*m_player->Draw(time, seconds);
	m_bunniesMgr->Draw(time, seconds);*/

	shader->UseProgram();
	shader->SetMatrixParameter("u_viewProj", sm::Matrix::PerspectiveMatrix(60.0f, 1.0f, 0.1f, 100.0f));
	shader->SetMatrixParameter("u_world", sm::Matrix::TranslateMatrix(0, 0, -80));

	std::vector<MeshPart*> meshParts;
	model->GetMeshParts(meshParts);
	meshParts[1]->Draw();
}

void GameScreen::Update(float time, float seconds)
{
	m_activeGun->Update(time, seconds);
	IBullet *bullet = m_activeGun->GetBullet();
	if (bullet != NULL)
	{
		bullet->TakeDamage(this);
	}

	m_player->Update(time, seconds);
	m_bunniesMgr->Update(time, seconds);
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

