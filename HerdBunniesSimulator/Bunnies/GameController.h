#pragma once

#include <UI/IGestureHandler.h>
#include "IGameController.h"
#include <stdint.h>
#include <string>

#include "Player.h" // TODO PROTO

class IGraphicsEngine;
class IScreen;
class GameScreen;
class SplashScreen;
class MainMenuScreen;
class Content;

class GameController : public IGameController
{
public:
	GameController(IGraphicsEngine *graphicsEngine);
	~GameController(void);

	bool Initialize();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

	void HandleTapGesture(const sm::Vec2 &point);
	void HandlePress(uint32_t pointIndex, const sm::Vec2 &point);
    void HandleRelease(uint32_t pointIndex, const sm::Vec2 &point);
	void HandleMove(uint32_t pointIndex, const sm::Vec2 &point);

	void proto_SetStrafeMove(float value);
	void proto_SetForwardMove(float value);
	void proto_SetLookTarget(const sm::Vec3 &lookTarget);
	Player* proto_GetPlayer();

	void ShowGameScreen();
	void ShowMainMenuScreen();

private:
	GameScreen *m_gameScreen;
	SplashScreen *m_splashScreen;
	MainMenuScreen *m_mainMenuScreen;

	IGraphicsEngine *m_graphicsEngine;
	Content *m_content;

	IScreen *m_activeScreen;

	bool InitializeGraphics(const std::string &basePath);
};

