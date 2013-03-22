#include "Shotgun.h"
#include "ShotgunBullet.h"
#include "GameProps.h"
#include "Player.h"
#include "InterfaceProvider.h"
#include "Environment.h"

#include <Graphics/Shader.h>
#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/MeshPart.h>
#include <Graphics/Texture.h>
#include <Graphics/Content/Content.h>

#include <stddef.h>

Shotgun::Shotgun(Player *player) :
	m_player(player),
	m_shotTicker(GameProps::ShotgunShotDelay),
	m_isTriggerPulled(false),
	m_justShooted(false)
{
	m_celShadingShader = InterfaceProvider::GetContent()->Get<Shader>("CelShading");
	m_outlineShader = InterfaceProvider::GetContent()->Get<Shader>("Outline");
	m_celLightTex = InterfaceProvider::GetContent()->Get<Texture>("cel_light");
	m_rifleTex = InterfaceProvider::GetContent()->Get<Texture>("shotgun_rifle");
	m_handTex = InterfaceProvider::GetContent()->Get<Texture>("shotgun_hand");
	m_shotgunModel = InterfaceProvider::GetContent()->Get<Model>("shotgun");

	m_celShadingShader->BindVertexChannel(0, "a_position");
	m_celShadingShader->BindVertexChannel(1, "a_normal");
	m_celShadingShader->BindVertexChannel(2, "a_coords");
	m_celShadingShader->LinkProgram();

	m_outlineShader->BindVertexChannel(0, "a_position");
	m_outlineShader->BindVertexChannel(1, "a_normal");
	m_outlineShader->LinkProgram();

	m_shotTicker.Progress(GameProps::ShotgunShotDelay); // be ready for shot

	m_shotgunBullet = new ShotgunBullet();
}

Shotgun::~Shotgun(void)
{
}

void Shotgun::PullTrigger()
{
	m_isTriggerPulled = true;
}

void Shotgun::ReleaseTrigger()
{
	m_isTriggerPulled = false;
	m_justShooted = false;
}

void Shotgun::Update(float time, float seconds)
{
	m_shotTicker.Progress(seconds);
	m_justShooted = false;

	if (m_isTriggerPulled)
	{
		if (m_shotTicker.IsTimeout())
		{
			m_shotTicker.Reset();
			m_shotgunBullet->SetParams(m_player->GetPosition(), m_player->GetLookTarget());
			m_justShooted = true;
		}
	}
}

void Shotgun::Draw(float time, float seconds)
{
	float width = Environment::GetInstance()->GetScreenWidth();
	float height = Environment::GetInstance()->GetScreenHeight();

	sm::Matrix projMatrix = sm::Matrix::PerspectiveMatrix(45.0f, width / height, 0.1f, 100.0f);
	sm::Matrix worldMatrix = sm::Matrix::TranslateMatrix(0, 0, 0);

	std::vector<MeshPart*> meshParts;
	m_shotgunModel->GetMeshParts(meshParts);

	glDepthMask(GL_FALSE);

	m_outlineShader->UseProgram();
	m_outlineShader->SetMatrixParameter("u_mvpMatrix", projMatrix * worldMatrix);
	m_outlineShader->SetParameter("u_outlineWidth", 0.02f);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	meshParts[0]->Draw();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	meshParts[1]->Draw();

	glDepthMask(GL_TRUE);

	m_celShadingShader->UseProgram();
	m_celShadingShader->SetMatrixParameter("u_viewProjMatrix", projMatrix);
	m_celShadingShader->SetMatrixParameter("u_worldMatrix", worldMatrix);
	m_celShadingShader->SetTextureParameter("u_celLight", 1, m_celLightTex->GetId());
	m_celShadingShader->SetParameter("u_lightPosition", -5.0f, 30.0f, -5.0f);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	m_celShadingShader->SetTextureParameter("u_diffTex", 0, m_rifleTex->GetId());
	meshParts[0]->Draw();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	m_celShadingShader->SetTextureParameter("u_diffTex", 0, m_handTex->GetId());
	meshParts[1]->Draw();
}

IBullet* Shotgun::GetBullet() const
{
	return m_justShooted ? m_shotgunBullet : NULL;
}

