#pragma once

#include "IBullet.h"

class ShotgunBullet : public IBullet
{
public:
	ShotgunBullet(void);
	~ShotgunBullet(void);

	void Update(float time, float seconds);
	void Draw(float time, float seconds);
};

