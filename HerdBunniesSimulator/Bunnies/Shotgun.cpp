#include "Shotgun.h"
#include "ShotgunBullet.h"
#include <stddef.h>

Shotgun::Shotgun(void)
{
	m_shotgunBullet = new ShotgunBullet();
}

Shotgun::~Shotgun(void)
{
}

void Shotgun::PullTrigger()
{
}

void Shotgun::ReleaseTrigger()
{
}

void Shotgun::Update(float time, float seconds)
{
}

void Shotgun::Draw(float time, float seconds)
{
}

IBullet* Shotgun::GetBullet() const
{
	return m_shotgunBullet;
}

