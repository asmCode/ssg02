#pragma once

#include <UI/IGestureHandler.h>
#include "IGameController.h"
#include <stdint.h>

#include "Player.h" // TODO PROTO

class IScreen;
class GameScreen;

class GameController : public IGameController
{
public:
	GameController(void);
	~GameController(void);

	bool Initialize();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

	void HandlePress(uint32_t pointIndex, const sm::Vec2 &point);
    void HandleRelease(uint32_t pointIndex, const sm::Vec2 &point);
	void HandleMove(uint32_t pointIndex, const sm::Vec2 &point);

	void proto_SetStrafeMove(float value);
	void proto_SetForwardMove(float value);
	void proto_SetLookTarget(const sm::Vec3 &lookTarget);
	Player* proto_GetPlayer();

private:
	GameScreen *m_gameScreen;

	IScreen *m_activeScreen;
};

