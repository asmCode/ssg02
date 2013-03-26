#include "Shotgun.h"
#include "ShotgunBullet.h"
#include "GameProps.h"
#include "Player.h"
#include "InterfaceProvider.h"
#include "Environment.h"
#include "DrawingRoutines.h"
#include "SpritesMap.h"

#include <Graphics/SpriteBatch.h>
#include <Graphics/TexPart.h>
#include <Graphics/Model.h>
#include <Graphics/Animation.h>
#include <Graphics/Content/Content.h>

#include <stddef.h>

Shotgun::Shotgun(Player *player) :
	m_player(player),
	m_shotTicker(GameProps::ShotgunShotDelay),
	m_isTriggerPulled(false),
	m_justShooted(false),
	m_shootProgress(0.0f)
{
	m_shotgunModel = InterfaceProvider::GetContent()->Get<Model>("shotgun");
	m_shotAnimation = InterfaceProvider::GetContent()->Get<Animation>("shotgun");

	m_shotAnimation->AssignModel(m_shotgunModel);
	m_shotAnimLength = m_shotAnimation->GetAnimLength();

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

static sm::Matrix CalcBoneMatrixZ(const sm::Vec3 &jointStart, const sm::Vec3 &jointEnd)
{
	sm::Matrix rot = sm::Matrix::IdentityMatrix();

	sm::Vec3 zAxis = (jointEnd - jointStart).GetNormalized().GetReversed();
	sm::Vec3 xAxis = (zAxis * sm::Vec3(0, 1, 0)).GetNormalized();
	sm::Vec3 yAxis = xAxis * zAxis;

	rot.a[0] = xAxis.x;
	rot.a[1] = xAxis.y;
	rot.a[2] = xAxis.z;

	rot.a[4] = yAxis.x;
	rot.a[5] = yAxis.y;
	rot.a[6] = yAxis.z;

	rot.a[8] = zAxis.x;
	rot.a[9] = zAxis.y;
	rot.a[10] = zAxis.z;

	return sm::Matrix::TranslateMatrix(jointStart) * rot;
}

sm::Vec3 p, t;

void Shotgun::Update(float time, float seconds)
{
	m_shotTicker.Progress(seconds);
	m_justShooted = false;

	if (m_isTriggerPulled)
	{
		if (m_shotTicker.IsTimeout())
		{
			m_shotTicker.Reset();
			m_shotgunBullet->SetParams(m_player->GetEyePosition(), m_player->GetLookTarget());
			p = m_player->GetEyePosition();
			t = m_player->GetLookTarget();
			m_justShooted = true;

			m_shootProgress = 0.0f;
		}
	}

	if (m_shootProgress < m_shotAnimLength)
	{
		m_shotAnimation->Update(m_shootProgress, sm::Matrix::IdentityMatrix(), seconds);
		m_shootProgress += seconds;
		if (m_shootProgress > m_shotAnimLength)
		{
			m_shotAnimation->Update(0.0f, sm::Matrix::IdentityMatrix(), seconds);
			m_shootProgress = m_shotAnimLength;
		}
	}
}

void Shotgun::Draw(float time, float seconds)
{
	DrawingRoutines::SetOutlineWidth(0.02f);
	DrawingRoutines::DrawCelShaded(InterfaceProvider::GetContent()->Get<Model>("cylinder"), m_player->GetViewMatrix(), CalcBoneMatrixZ(p, p + t));
	//DrawingRoutines::DrawCelShaded(InterfaceProvider::GetContent()->Get<Model>("cylinder"), m_player->GetViewMatrix(), sm::Matrix::TranslateMatrix(0, 4, 0));
	DrawingRoutines::DrawCelShaded(m_shotgunModel, sm::Matrix::IdentityMatrix(), sm::Matrix::IdentityMatrix());

	SpritesMap *spritesMap = InterfaceProvider::GetSpritesMap();


	InterfaceProvider::GetSpriteBatch()->Begin();
	InterfaceProvider::GetSpriteBatch()->Draw(*spritesMap->GetTexPart("crosshair"), (960 - 18) / 2, (640 - 18) / 2);
	InterfaceProvider::GetSpriteBatch()->End();
}

IBullet* Shotgun::GetBullet() const
{
	return m_justShooted ? m_shotgunBullet : NULL;
}

