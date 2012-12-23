#include "ShotgunBullet.h"
#include "IDamageableProvider.h"
#include "IDamageable.h"
#include "GameProps.h"
#include <stddef.h>
#include <assert.h>

ShotgunBullet::ShotgunBullet(void)
{
}

ShotgunBullet::~ShotgunBullet(void)
{
}

void ShotgunBullet::Update(float time, float seconds)
{
}

void ShotgunBullet::Draw(float time, float seconds)
{
}

void ShotgunBullet::TakeDamage(IDamageableProvider *damageableProvider)
{
	assert(damageableProvider != NULL);

	static IDamageable *damageables[200]; // TODO
	uint32_t count;

	damageableProvider->GetDamageablesInCone((IDamageable**)damageables, count, m_position, m_direction, GameProps::ShotgunFieldOfDamage);

	for (uint32_t i = 0; i < count; i++)
	{
		damageables[i]->MakeDamage(GameProps::ShotgunDamage);
	}
}

void ShotgunBullet::SetParams(const sm::Vec3 &position, const sm::Vec3 &direction)
{
	m_position = position;
	m_direction = direction;
}

