#pragma once

#include "IGun.h"

class ShotgunBullet;

class Shotgun : public IGun
{
public:
	Shotgun(void);
	~Shotgun(void);

	void PullTrigger();
	void ReleaseTrigger();

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

	IBullet* GetBullet() const;

private:
	ShotgunBullet *m_shotgunBullet;
};

