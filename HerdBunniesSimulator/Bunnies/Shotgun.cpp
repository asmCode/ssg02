#include "Shotgun.h"
#include "ShotgunBullet.h"
#include "GameProps.h"
#include "Player.h"
#include <stddef.h>

Shotgun::Shotgun(Player *player) :
	m_player(player),
	m_shotTicker(GameProps::ShotgunShotDelay),
	m_isTriggerPulled(false),
	m_justShooted(false)
{
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
}

IBullet* Shotgun::GetBullet() const
{
	return m_justShooted ? m_shotgunBullet : NULL;
}

