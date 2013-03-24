#include "Shotgun.h"
#include "ShotgunBullet.h"
#include "GameProps.h"
#include "Player.h"
#include "InterfaceProvider.h"
#include "Environment.h"
#include "DrawingRoutines.h"

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
	DrawingRoutines::DrawCelShaded(m_shotgunModel, sm::Matrix::IdentityMatrix(), sm::Matrix::IdentityMatrix());
}

IBullet* Shotgun::GetBullet() const
{
	return m_justShooted ? m_shotgunBullet : NULL;
}

