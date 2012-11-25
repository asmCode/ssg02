#ifndef _HEALTHY_BUNNY_
#define _HEALTHY_BUNNY_

#include "IBunny.h"
#include <Math\Vec3.h>

class IBunnyState;

class HealthyBunny : public IBunny
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

private:
	bool m_isActive;

	IBunnyState *m_bunnyState;

	sm::Vec3 m_position;
	sm::Vec3 m_moveTarget;

	HealthyBunny *m_reproductionPartner;
	float m_reproductingTime;
	float m_restingAfterReproduction;
};

#endif

