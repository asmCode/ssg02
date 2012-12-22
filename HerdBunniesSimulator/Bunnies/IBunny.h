#ifndef _IBUNNY_
#define _IBUNNY_

#include <Math/Vec3.h>

class IBunnyState;

class IBunny
{
public:
	virtual void SetState(IBunnyState *bunnyState) = 0;
	virtual const IBunnyState *GetState() const = 0;

	virtual void SetPosition(const sm::Vec3 &position) = 0;
	virtual void SetMoveTarget(const sm::Vec3 &moveTarget) = 0;

	virtual const sm::Vec3 GetPosition() const = 0;
	virtual const sm::Vec3 GetMoveTarget() const = 0;

	virtual void MakeDamage(float damageValue) = 0;
};

#endif

