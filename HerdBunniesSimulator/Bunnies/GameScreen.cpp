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
	m_player = new Player();
	m_bunniesMgr = new BunniesManager();
	m_bunniesMgr->ResetForNewGame(4);

	Idle::GetInstance()->Initialize(m_player);
	SettingsInRanks::GetInstance()->Initialize(m_player, m_bunniesMgr);
	Reproducting::GetInstance()->Initialize(m_player, m_bunniesMgr);
	Respawning::GetInstance()->Initialize(m_bunniesMgr);
	RestingAfterFucking::GetInstance()->Initialize(m_bunniesMgr);
	BeeingFucked::GetInstance()->Initialize(m_bunniesMgr);
	ChangingToInfected::GetInstance()->Initialize(m_bunniesMgr);

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

