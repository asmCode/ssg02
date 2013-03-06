#include "GameController.h"

#include "IScreen.h"
#include "GameScreen.h"
#include "../BunniesView/WinShapesRenderer.h"
#include "InterfaceProvider.h"
#include <Graphics/IGraphicsEngine.h>
#include <Graphics/Content/Content.h>
#include <stddef.h>
#include <assert.h>

GameController::GameController(IGraphicsEngine *graphicsEngine) :
	m_graphicsEngine(graphicsEngine),
	m_gameScreen(NULL),
	m_activeScreen(NULL)
{
}

GameController::~GameController(void)
{
}

bool GameController::Initialize(const std::string &basePath)
{
	WinShapesRenderer *winShapeRenderer = new WinShapesRenderer();
	InterfaceProvider::m_shapesRenderer = winShapeRenderer;
	InterfaceProvider::m_graphicsEngine = m_graphicsEngine;

	m_content = new Content(m_graphicsEngine);
	m_content->LoadTextures(basePath + "/data/gui/");
	Texture *tex = m_content->Get<Texture>("SplashScreen");

	m_gameScreen = new GameScreen();
	if (!m_gameScreen->Initialize())
		return false;

	m_activeScreen = m_gameScreen;

	return true;
}

void GameController::Draw(float time, float seconds)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->Draw(time, seconds);
}

void GameController::Update(float time, float seconds)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->Update(time, seconds);
}

void GameController::HandlePress(uint32_t pointIndex, const sm::Vec2 &point)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->HandlePress(pointIndex, point);
}

void GameController::HandleRelease(uint32_t pointIndex, const sm::Vec2 &point)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->HandleRelease(pointIndex, point);
}

void GameController::HandleMove(uint32_t pointIndex, const sm::Vec2 &point)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->HandleMove(pointIndex, point);
}

void GameController::proto_SetStrafeMove(float value)
{
	Player *player = m_gameScreen->GetPlayer();

	player->SetStrafeMove(value);
}

void GameController::proto_SetForwardMove(float value)
{
	Player *player = m_gameScreen->GetPlayer();

	player->SetForwardMove(value);
}

void GameController::proto_SetLookTarget(const sm::Vec3 &lookTarget)
{
}

Player* GameController::proto_GetPlayer()
{
	return m_gameScreen->GetPlayer();
}

