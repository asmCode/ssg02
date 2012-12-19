#include "GameScreen.h"

#include "Player.h"
#include "BunniesManager.h"
#include "Idle.h"
#include "SettingsInRanks.h"
#include "Reproducting.h"
#include "ChangingToInfected.h"
#include "Respawning.h"
#include "RestingAfterFucking.h"
#include "BeeingFucked.h"

#include "../BunniesView/IShapesRenderer.h"
#include "../BunniesView/WinShapesRenderer.h"

GameScreen::GameScreen(void)
{
}

GameScreen::~GameScreen(void)
{
}

bool GameScreen::Initialize()
{
	// SHAPE RENDERER MUSISZ DOSTARCZYC Z ZEWNATRZ shapesRenderer = new WinShapesRenderer();

	player = new Player(shapesRenderer);
	bunniesMgr = new BunniesManager(shapesRenderer);
	bunniesMgr->ResetForNewGame(2);

	Idle::GetInstance()->Initialize(player);
	SettingsInRanks::GetInstance()->Initialize(player, bunniesMgr);
	Reproducting::GetInstance()->Initialize(player, bunniesMgr);
	Respawning::GetInstance()->Initialize(bunniesMgr);
	RestingAfterFucking::GetInstance()->Initialize(bunniesMgr);
	BeeingFucked::GetInstance()->Initialize(bunniesMgr);
	ChangingToInfected::GetInstance()->Initialize(bunniesMgr);

	return true;
}

bool GameScreen::InitResources()
{
	return false;
}

bool GameScreen::ReleaseResources()
{
	return false;
}

void GameScreen::Draw(float time, float seconds)
{
	m_player->Draw(time, seconds);
	m_bunniesMgr->Draw(time, seconds);
}

void GameScreen::Update(float time, float seconds)
{
	m_player->Update(time, seconds);
	m_bunniesMgr->Update(time, seconds);
}

void GameScreen::HandlePress(uint32_t pointIndex, const sm::Vec2 &point)
{
}

void GameScreen::HandleRelease(uint32_t pointIndex, const sm::Vec2 &point)
{
}

void GameScreen::HandleMove(uint32_t pointIndex, const sm::Vec2 &point)
{
}

Player* GameScreen::GetPlayer()
{
	return m_player;
}

