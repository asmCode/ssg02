#include "GameController.h"

#include "IScreen.h"
#include "GameScreen.h"
#include "SplashScreen.h"
#include "../BunniesView/WinShapesRenderer.h"
#include "InterfaceProvider.h"
#include <Graphics/IGraphicsEngine.h>
#include <Graphics/Content/Content.h>
#include <Graphics/SpriteBatch.h>
#include <stddef.h>
#include <assert.h>

GameController::GameController(IGraphicsEngine *graphicsEngine) :
	m_graphicsEngine(graphicsEngine),
	m_gameScreen(NULL),
	m_splashScreen(NULL),
	m_activeScreen(NULL)
{
}

GameController::~GameController(void)
{
}

bool GameController::InitializeGraphics(const std::string &basePath)
{
	WinShapesRenderer *winShapeRenderer = new WinShapesRenderer();

	m_content = new Content(m_graphicsEngine);
	m_content->LoadTextures(basePath + "/data/gui/");
	m_content->LoadShaders(basePath + "/data/shaders/");

	Shader *shader = m_content->Get<Shader>("sprite");

	SpriteBatch *spriteBatch = new SpriteBatch(shader, sm::Matrix::Ortho2DMatrix(0, 800, 800, 0));

	InterfaceProvider::m_shapesRenderer = winShapeRenderer;
	InterfaceProvider::m_graphicsEngine = m_graphicsEngine;
	InterfaceProvider::m_content = m_content;
	InterfaceProvider::m_spriteBatch = spriteBatch;
	
	return true;
}

bool GameController::Initialize(const std::string &basePath)
{
	if (!InitializeGraphics(basePath))
	{
		assert(false);
		return false;
	}

	m_gameScreen = new GameScreen();
	if (!m_gameScreen->Initialize())
		return false;

	m_splashScreen = new SplashScreen();
	if (!m_splashScreen->InitResources())
		return false;

	m_activeScreen = m_splashScreen;

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

