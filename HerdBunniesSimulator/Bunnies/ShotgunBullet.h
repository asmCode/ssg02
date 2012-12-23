#pragma once

#include "IBullet.h"

class ShotgunBullet : public IBullet
{
public:
	ShotgunBullet(void);
	~ShotgunBullet(void);

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

	void TakeDamage(IDamageableProvider *damageableProvider);

	void SetParams(const sm::Vec3 &position, const sm::Vec3 &direction);

private:
	sm::Vec3 m_position;
	sm::Vec3 m_direction;
};

