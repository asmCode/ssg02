#include "GameController.h"

#include "IScreen.h"
#include "GameScreen.h"
#include <stddef.h>
#include <assert.h>

GameController::GameController(void) :
	m_gameScreen(NULL),
	m_activeScreen(NULL)
{
}

GameController::~GameController(void)
{
}

bool GameController::Initialize()
{
	return false;
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
}

void GameController::proto_SetForwardMove(float value)
{
}

void GameController::proto_SetLookTarget(const sm::Vec3 &lookTarget)
{
}

Player* GameController::proto_GetPlayer()
{
	return m_gameScreen->GetPlayer();
}

