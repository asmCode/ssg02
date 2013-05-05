#ifndef _HEALTHY_BUNNY_
#define _HEALTHY_BUNNY_

#include "Bunny.h"
#include "Ticker.h"
#include <Math\Vec3.h>
#include <Math\Matrix.h>

class IBunnyState;
class InfectedBunny;
class Model;
class Animation;

class HealthyBunny : public Bunny
{
	friend class SettingsInRanks;
	friend class Reproducting;
	friend class GoingToReproduction;
	friend class RunningAway;
	friend class BeeingFucked;
	friend class Idle;

public:
	HealthyBunny(void);
	~HealthyBunny(void);

	void Update(float time, float seconds);
	void Draw(float time, float seconds, const sm::Matrix &viewMatrix);

	void Reset();

	bool IsActive() const;

	void ActivateOnStart(const sm::Vec3 &position);

	/**
	 * @param isActive if true, then during fucking bunny have m_fuckAnim animation.
	                   Otherwise it is passive and is not moving.  
	 */
	void StartReproductionProcess(HealthyBunny *partner, bool isActive);

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
	void SetToBeeingFucked(Bunny *infectedBunny); // hunting bunny gotcha!
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

	bool m_useTransform;
	bool m_mixTransform;
	sm::Matrix m_transform;

	IBunnyState *m_bunnyState;

	Model *m_bunnyModel;
	Model *m_babyModel;
	Animation *m_walkAnim;
	Animation *m_runAnim;
	Animation *m_fuckAnim;
	Animation *m_babyWalkAnim;

	bool m_useRunningAwayInitialDirection;
	sm::Vec3 m_runningAwayInitialDirection;

	HealthyBunny *m_reproductionPartner;
	bool m_isActiveReproducer;
	float m_reproductingTime;
	float m_restingAfterReproduction;
	Ticker m_changingProgress;

	float m_growingUpTime;
	sm::Vec3 m_borningJumpOutVector;
	sm::Vec3 m_borningJumpOutAxis;
	float m_targetPositionRefreshColldown;

	float m_fuckProgressTime;
	int m_fuckMoveCycles;

	bool m_isAssExposed;
	float m_exposeAssAnimTime;
	float m_exposeAssAngleDiff;
	sm::Vec3 m_exposeAssBaseTarget;
	sm::Vec3 m_exposeAssAxis;
};

#endif

