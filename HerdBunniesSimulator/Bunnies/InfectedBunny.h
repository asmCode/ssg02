#ifndef _INFECTED_BUNNY_
#define _INFECTED_BUNNY_

#include "IBunny.h"

class IBunnyState;
class HealthyBunny;

class InfectedBunny : public IBunny
{
public:
	InfectedBunny(void);
	~InfectedBunny(void);

	bool IsActive() const;

	void SetState(IBunnyState *bunnyState);
	const IBunnyState *GetState() const;

	void SetPosition(const sm::Vec3 &position);
	void SetMoveTarget(const sm::Vec3 &moveTarget);

	const sm::Vec3 GetPosition() const;
	const sm::Vec3 GetMoveTarget() const;

	void Update(float time, float seconds);

	void Respawn(const sm::Vec3 &position);

	void Reset();

	float IsSpawning() const;
	void DecreaseSpawningProcess(float seconds);
	void SetHuntingTarget(HealthyBunny *healthyBunny);
	HealthyBunny *GetHuntingTarget();

	const sm::Vec3& GetTargetPosition() const;
	void SetTargetPosition(const sm::Vec3 &targetPosition);

	void RefreshNewTargetPosition(float seconds);

	float& FuckingProgress();
	float& RestingAfterFuckingProgress();

private:
	bool m_isActive;

	IBunnyState *m_bunnyState;

	sm::Vec3 m_position;
	sm::Vec3 m_moveTarget;

	float m_targetPositionRefreshColldown;
	sm::Vec3 m_targetPosition; // target which bunny should reach

	float m_fuckingProgress;
	float m_restingAfterFuckingProgress;

	float m_spawningProgress;
	HealthyBunny *m_huntingTarget;
};

#endif

