#include "GameController.h"

#include "IScreen.h"
#include "GameScreen.h"
#include "SplashScreen.h"
#include "MainMenuScreen.h"
#include "SpritesMap.h"
#include "Environment.h"
#include "Control.h"
#include "DrawingRoutines.h"
#include "../BunniesView/WinShapesRenderer.h"
#include "InterfaceProvider.h"
#include <Graphics/IGraphicsEngine.h>
#include <Graphics/Content/Content.h>
#include <Graphics/Model.h>
#include <Graphics/Animation.h>
#include <Graphics/SpriteBatch.h>
#include <stddef.h>
#include <assert.h>

GameController::GameController(IGraphicsEngine *graphicsEngine) :
	m_graphicsEngine(graphicsEngine),
	m_splashScreen(NULL),
	m_mainMenuScreen(NULL),
	m_gameScreen(NULL),
	m_activeScreen(NULL)
{
}

GameController::~GameController(void)
{
}

bool GameController::InitializeGraphics(const std::string &basePath)
{
	WinShapesRenderer *winShapeRenderer = new WinShapesRenderer();

	uint32_t screenWidth = Environment::GetInstance()->GetScreenWidth();
	uint32_t screenHeight = Environment::GetInstance()->GetScreenHeight();

	m_content = new Content(m_graphicsEngine);
	InterfaceProvider::m_content = m_content;
	m_content->LoadTextures(basePath + "/data/gui/");
	m_content->LoadTextures(basePath + "/data/textures/");
	m_content->LoadShaders(basePath + "/data/shaders/");
	m_content->LoadModels(basePath + "/data/models/");
	m_content->LoadAnimations(basePath + "/data/animations/");
	m_content->LoadMaterials(basePath + "/data/materials/");
	m_content->CombineResources();

	m_content->Get<Texture>("grass")->BindTexture();
	m_content->Get<Texture>("grass")->SetFilterModel(Texture::Filter_LinearMipmapLinear, Texture::Filter_Linear);
	m_content->Get<Texture>("grass")->SetWrappingMode(Texture::Wrap_Repeat);
	m_content->Get<Texture>("grass")->GenerateMipmaps();

	m_content->Get<Texture>("field")->BindTexture();
	m_content->Get<Texture>("field")->SetFilterModel(Texture::Filter_LinearMipmapLinear, Texture::Filter_Linear);
	m_content->Get<Texture>("field")->SetWrappingMode(Texture::Wrap_Repeat);
	m_content->Get<Texture>("field")->GenerateMipmaps();

	m_content->Get<Animation>("shotgun")->AssignModel(m_content->Get<Model>("shotgun"));
	m_content->Get<Animation>("hbunny_walk")->AssignModel(m_content->Get<Model>("hbunny"));
	m_content->Get<Animation>("hbunny_run")->AssignModel(m_content->Get<Model>("hbunny"));
	m_content->Get<Animation>("hbunny_fuck")->AssignModel(m_content->Get<Model>("hbunny"));
	m_content->Get<Animation>("ibunny_run")->AssignModel(m_content->Get<Model>("ibunny"));
	m_content->Get<Animation>("ibunny_walk")->AssignModel(m_content->Get<Model>("ibunny"));
	m_content->Get<Animation>("ibunny_fuck")->AssignModel(m_content->Get<Model>("ibunny"));
	m_content->Get<Animation>("baby_walk")->AssignModel(m_content->Get<Model>("baby"));

	m_content->Get<Animation>("leg")->AssignModel(m_content->Get<Model>("leg"));

	DrawingRoutines::Initialize();
	DrawingRoutines::SetLightPosition(sm::Vec3(-100.0f, 500.0f, -100.0f));
	DrawingRoutines::SetProjectionMatrix(sm::Matrix::PerspectiveMatrix(45.0f, static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 1000.0f));

	Shader *shader = m_content->Get<Shader>("sprite");

	SpriteBatch *spriteBatch = new SpriteBatch(shader, sm::Matrix::Ortho2DMatrix(0, screenWidth, screenHeight, 0));

	SpritesMap *spritesMap = new SpritesMap();
	if (!spritesMap->LoadFromFile(basePath + "/data/gui/SpritesMap.xml", m_content))
		return false;

	InterfaceProvider::m_shapesRenderer = winShapeRenderer;
	InterfaceProvider::m_graphicsEngine = m_graphicsEngine;
	InterfaceProvider::m_spriteBatch = spriteBatch;
	InterfaceProvider::m_spritesMap = spritesMap;

	Control::SetSpriteBatch(spriteBatch);
	
	return true;
}

bool GameController::Initialize()
{
	std::string basePath = Environment::GetInstance()->GetBasePath();

	if (!InitializeGraphics(basePath))
	{
		assert(false);
		return false;
	}

	m_gameScreen = new GameScreen();
	if (!m_gameScreen->Initialize())
		return false;

	m_splashScreen = new SplashScreen(this);
	if (!m_splashScreen->InitResources())
		return false;

	m_mainMenuScreen = new MainMenuScreen(this);
	if (!m_mainMenuScreen->InitResources())
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

void GameController::HandleTapGesture(const sm::Vec2 &point)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->HandleTapGesture(point);
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

void GameController::ShowGameScreen()
{
	m_activeScreen = m_gameScreen;
}

void GameController::ShowMainMenuScreen()
{
	m_activeScreen = m_mainMenuScreen;
}

bool GameController::proto_IsInGame()
{
	return dynamic_cast<GameScreen*>(m_activeScreen) != NULL;
}

