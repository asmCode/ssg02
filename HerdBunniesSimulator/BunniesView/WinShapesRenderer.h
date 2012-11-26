#pragma once

#include "IShapesRenderer.h"
#include <Math/Vec3.h>

class WinShapesRenderer : public IShapesRenderer
{
public:
	WinShapesRenderer(void);
	~WinShapesRenderer(void);

	void DrawHealthyBunny(HealthyBunny *healthyBunny);
	void DrawPlayer(Player *player);

private:
	sm::Vec3 GetBunnyColor(HealthyBunny *healtyBunny);
};

