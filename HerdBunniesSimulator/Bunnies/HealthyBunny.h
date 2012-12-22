#ifndef _HEALTHY_BUNNY_
#define _HEALTHY_BUNNY_

#include "Bunny.h"
#include "Ticker.h"
#include <Math\Vec3.h>

class IBunnyState;
class InfectedBunny;

class HealthyBunny : public Bunny
{
public:
	HealthyBunny(void);
	~HealthyBunny(void);

	void Update(float time, float seconds);

	void Reset();

	bool IsActive() const;

	void ActivateOnStart(const sm::Vec3 &position);

	void SetReproductionPartner(HealthyBunny *bunny);
	HealthyBunny *GetReproductionPartner();

	void SetReproductingTime(float time);
	float GetReproductingTime() const;

	void SetRestingAfterReproductionTime(float time);

	void SetState(IBunnyState *bunnyState);
	const IBunnyState *GetState() const;

	void SetPosition(const sm::Vec3 &position);
	void SetMoveTarget(const sm::Vec3 &moveTarget);
	const sm::Vec3 GetPosition() const;
	const sm::Vec3 GetMoveTarget() const;

	bool CanReproduce() const;
	void DecreaseRestingAfterReproductionTime(float seconds);

	void SetNewborn();
	bool IsBorning() const;
	bool IsGrowingUp() const;
	float GetGrowingUpTime() const;
	void DecreaseGrowingUpTime(float seconds);
	const sm::Vec3 &GetBorningJumpOutVector() const;

	bool CanBeFucked() const;

	void GetTheFuckOut(InfectedBunny *ibunny); // run away from hunting bunny
	void SetToBeeingFucked(); // hunting bunny gotcha!
	void SetToIdle();

	void RefreshNewTargetPosition(float seconds);

	const sm::Vec3& GetTargetPosition() const;
	void SetTargetPosition(const sm::Vec3 &targetPosition);

	void StartChangingToInfected();
	Ticker& ChangingProgress();

	void MakeDamage(float damageValue);

	void Die();

private:
	bool m_isActive;

	IBunnyState *m_bunnyState;

	bool m_useRunningAwayInitialDirection;
	sm::Vec3 m_runningAwayInitialDirection;

	sm::Vec3 m_position;
	sm::Vec3 m_moveTarget;

	HealthyBunny *m_reproductionPartner;
	float m_reproductingTime;
	float m_restingAfterReproduction;
	Ticker m_changingProgress;

	float m_growingUpTime;
	sm::Vec3 m_borningJumpOutVector;
	float m_targetPositionRefreshColldown;
	sm::Vec3 m_targetPosition; // target which bunny should reach
};

#endif

