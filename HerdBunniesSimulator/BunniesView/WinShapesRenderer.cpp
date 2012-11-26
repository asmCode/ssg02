#include "WinShapesRenderer.h"

#include "../Bunnies/Player.h"
#include "../Bunnies/HealthyBunny.h"
#include "../Bunnies/IBunnyState.h"
#include "Shapes.h"

WinShapesRenderer::WinShapesRenderer(void)
{
}

WinShapesRenderer::~WinShapesRenderer(void)
{
}

void WinShapesRenderer::DrawHealthyBunny(HealthyBunny *healthyBunny)
{
	sm::Vec3 color = GetBunnyColor(healthyBunny);

	if (healthyBunny->GetState()->GetStateType() == IBunnyState::State_GoingToReproduction)
		Shapes::DrawCircle(sm::Vec2(healthyBunny->GetPosition().x, healthyBunny->GetPosition().z), 0.4f, color);
	else
		Shapes::DrawCircle(sm::Vec2(healthyBunny->GetPosition().x, healthyBunny->GetPosition().z), 0.4f, color);
}

void WinShapesRenderer::DrawPlayer(Player *player)
{
	Shapes::DrawCircle(sm::Vec2(player->GetPosition().x, player->GetPosition().z), 0.5f, sm::Vec3(1, 0, 0));

	sm::Vec3 targetPosition = player->GetPosition() + (player->GetLookTarget() * 3.0f);
	Shapes::DrawCircle(sm::Vec2(targetPosition.x, targetPosition.z), 0.2f, sm::Vec3(1, 0, 0));
}

sm::Vec3 WinShapesRenderer::GetBunnyColor(HealthyBunny *healtyBunny)
{
	if (healtyBunny->IsBorning())
		return sm::Vec3(0, 1, 0);
	else if (healtyBunny->IsGrowingUp())
		return sm::Vec3(0, 0, 1);
	if (healtyBunny->GetState()->GetStateType() == IBunnyState::State_Idle ||
		healtyBunny->GetState()->GetStateType() == IBunnyState::State_SettingInRank)
		return sm::Vec3(218.0f / 255.0f, 112.0f / 255.0f, 214.0f / 255.0f);
	else if (healtyBunny->GetState()->GetStateType() == IBunnyState::State_GoingToReproduction)
		return sm::Vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f);
	else if (healtyBunny->GetState()->GetStateType() == IBunnyState::State_Reproducting)
		return sm::Vec3(255.0f / 255.0f, 128.0f / 255.0f, 0.0f / 255.0f);

	return sm::Vec3(1.0f, 1.0f, 1.0f);
}

