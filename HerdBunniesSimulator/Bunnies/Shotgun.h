#pragma once

#include "IGun.h"
#include "Ticker.h"

class ShotgunBullet;
class Player;

class Shotgun : public IGun
{
public:
	Shotgun(Player *player);
	~Shotgun(void);

	void PullTrigger();
	void ReleaseTrigger();

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

	IBullet* GetBullet() const;

private:
	Player *m_player;
	ShotgunBullet *m_shotgunBullet;

	bool m_isTriggerPulled;
	bool m_justShooted;

	Ticker m_shotTicker;
};

