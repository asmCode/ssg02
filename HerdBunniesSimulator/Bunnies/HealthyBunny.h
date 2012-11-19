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

	void SetState(IBunnyState *bunnyState);

	void SetPosition(const sm::Vec3 &position);
	void SetMoveTarget(const sm::Vec3 &moveTarget);
	const sm::Vec3 GetPosition() const;
	const sm::Vec3 GetMoveTarget() const;

private:
	bool m_isActive;

	IBunnyState *m_bunnyState;

	sm::Vec3 m_position;
	sm::Vec3 m_moveTarget;
};

#endif

