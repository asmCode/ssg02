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
#include <Windows.h>

#include "../BunniesView/IShapesRenderer.h"
#include "../BunniesView/WinShapesRenderer.h"

#include <Graphics/Shader.h>
#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/MeshPart.h>
#include <Graphics/Texture.h>
#include <Graphics/Content/Content.h>

Model *model;
Shader *shader;
Shader *outlineShader;
Texture *celLightTex;
Texture *woodTex;

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
	outlineShader = InterfaceProvider::GetContent()->Get<Shader>("Outline");
	celLightTex = InterfaceProvider::GetContent()->Get<Texture>("cel_light");
	woodTex = InterfaceProvider::GetContent()->Get<Texture>("wood");

	shader->BindVertexChannel(0, "a_position");
	shader->BindVertexChannel(1, "a_normal");
	shader->BindVertexChannel(2, "a_coords");
	shader->LinkProgram();

	outlineShader->BindVertexChannel(0, "a_position");
	outlineShader->BindVertexChannel(1, "a_normal");
	outlineShader->LinkProgram();

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

float rotate;

void GameScreen::Draw(float time, float seconds)
{
	m_activeGun->Draw(time, seconds);

	rotate += seconds;
	/*m_player->Draw(time, seconds);
	m_bunniesMgr->Draw(time, seconds);*/

	float width = Environment::GetInstance()->GetScreenWidth();
	float height = Environment::GetInstance()->GetScreenHeight();

	sm::Matrix projMatrix = sm::Matrix::PerspectiveMatrix(60.0f, width / height, 0.1f, 100.0f);
	//sm::Matrix worldMatrix = sm::Matrix::TranslateMatrix(0, -0, -10) * sm::Matrix::RotateAxisMatrix(rotate, 0, 1, 0);
	//sm::Matrix worldMatrix = sm::Matrix::TranslateMatrix(-1, -1, -1);
	sm::Matrix worldMatrix = sm::Matrix::TranslateMatrix(0, 0, 0);

	std::vector<MeshPart*> meshParts;
	//model->GetMeshParts(meshParts);
	//m_->GetMeshParts(meshParts);

	glDepthMask(GL_FALSE);

	outlineShader->UseProgram();
	outlineShader->SetMatrixParameter("u_mvpMatrix", projMatrix * worldMatrix);
	outlineShader->SetParameter("u_outlineWidth", 0.05f);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//meshParts[0]->Draw();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//meshParts[1]->Draw();

	glDepthMask(GL_TRUE);

	shader->UseProgram();
	shader->SetMatrixParameter("u_viewProjMatrix", projMatrix);
	shader->SetMatrixParameter("u_worldMatrix", worldMatrix);
	shader->SetTextureParameter("u_diffTex", 0, woodTex->GetId());
	shader->SetTextureParameter("u_celLight", 1, celLightTex->GetId());
	shader->SetParameter("u_lightPosition", 50.0f, 30.0f, 50.0f);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//meshParts[0]->Draw();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//meshParts[1]->Draw();
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

