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
	if (healthyBunny->GetState()->GetStateType() == IBunnyState::State_GoingToReproduction)
		Shapes::DrawCircle(sm::Vec2(healthyBunny->GetPosition().x, healthyBunny->GetPosition().z), 0.4f, sm::Vec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
	else
		Shapes::DrawCircle(sm::Vec2(healthyBunny->GetPosition().x, healthyBunny->GetPosition().z), 0.4f, sm::Vec3(218.0f / 255.0f, 112.0f / 255.0f, 214.0f / 255.0f));
}

void WinShapesRenderer::DrawPlayer(Player *player)
{
	Shapes::DrawCircle(sm::Vec2(player->GetPosition().x, player->GetPosition().z), 0.5f, sm::Vec3(1, 0, 0));

	sm::Vec3 targetPosition = player->GetPosition() + (player->GetLookTarget() * 3.0f);
	Shapes::DrawCircle(sm::Vec2(targetPosition.x, targetPosition.z), 0.2f, sm::Vec3(1, 0, 0));
}

