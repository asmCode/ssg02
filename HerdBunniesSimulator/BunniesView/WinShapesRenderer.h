#pragma once

#include "IShapesRenderer.h"
#include <Math/Vec3.h>

class HealthyBunny;
class InfectedBunny;

class WinShapesRenderer : public IShapesRenderer
{
public:
	WinShapesRenderer(void);
	~WinShapesRenderer(void);

	void DrawHealthyBunny(HealthyBunny *healthyBunny);
	void DrawInfectedBunny(InfectedBunny *infectedBunny);
	void DrawPlayer(Player *player);

private:
	sm::Vec3 GetBunnyColor(HealthyBunny *healtyBunny);
	sm::Vec3 GetBunnyColor(InfectedBunny *bunny);
};

