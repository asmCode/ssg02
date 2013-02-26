#ifndef _IGAME_CONTROLLER_
#define _IGAME_CONTROLLER_

#include <UI/IGestureHandler.h>
#include <Math/Vec3.h>

class Player;

class IGameController : public IGestureHandler
{
public:
	virtual bool Initialize() = 0;

	virtual void Draw(float time, float seconds) = 0;
	virtual void Update(float time, float seconds) = 0;

	virtual void proto_SetStrafeMove(float value) = 0;
	virtual void proto_SetForwardMove(float value) = 0;
	virtual void proto_SetLookTarget(const sm::Vec3 &lookTarget) = 0;
	virtual Player* proto_GetPlayer() = 0;
};

#endif

