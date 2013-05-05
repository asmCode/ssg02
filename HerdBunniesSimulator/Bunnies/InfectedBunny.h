#ifndef _INFECTED_BUNNY_
#define _INFECTED_BUNNY_

#include "Bunny.h"
#include "Ticker.h"
#include <Math/Matrix.h>

class Model;
class IBunnyState;
class HealthyBunny;
class Animation;

class InfectedBunny : public Bunny
{
	friend class RestingAfterFucking;
	friend class Hunting;
	friend class Fucking;

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
	void Draw(float time, float seconds, const sm::Matrix &viewMatrix);

	void Respawn(const sm::Vec3 &position);

	void Reset();

	float IsSpawning() const;
	void DecreaseSpawningProcess(float seconds);
	void SetHuntingTarget(HealthyBunny *healthyBunny);
	HealthyBunny *GetHuntingTarget();

	const sm::Vec3& GetTargetPosition() const;
	void SetTargetPosition(const sm::Vec3 &targetPosition);

	void RefreshNewTargetPosition(float seconds);

	Ticker& FuckingProgress();
	Ticker& RestingAfterFuckingProgress();

	bool& DidTellToGTFO();

	void ChangeFromInfected(HealthyBunny *hbunny);

	void MakeDamage(float damageValue);

	void Die();

private:
	bool m_isActive;

	IBunnyState *m_bunnyState;

	Model *m_bunnyModel;
	Animation *m_runAnim;
	Animation *m_walkAnim;
	Animation *m_fuckAnim;

	float m_targetPositionRefreshColldown;

	float m_fuckProgressTime;
	int m_fuckMoveCycles;

	Ticker m_fuckingProgress;
	Ticker m_restingAfterFuckingProgress;

	bool m_didTellToGTFO;

	float m_spawningProgress;
	HealthyBunny *m_huntingTarget;
};

#endif

