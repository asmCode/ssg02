#pragma once

#include "IScreen.h"

class Player;
class IShapesRenderer;
class BunniesManager;

class GameScreen : public IScreen
{
public:
	GameScreen(void);
	~GameScreen(void);

	bool Initialize();

	bool InitResources();
	bool ReleaseResources();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

	void HandlePress(uint32_t pointIndex, const sm::Vec2 &point);
    void HandleRelease(uint32_t pointIndex, const sm::Vec2 &point);
	void HandleMove(uint32_t pointIndex, const sm::Vec2 &point);

	Player* GetPlayer();

private:
	Player *m_player;
	IShapesRenderer *m_shapesRenderer;
	BunniesManager *m_bunniesMgr;
};

