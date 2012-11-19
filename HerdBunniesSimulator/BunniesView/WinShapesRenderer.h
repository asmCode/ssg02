#pragma once

#include "IShapesRenderer.h"

class WinShapesRenderer : public IShapesRenderer
{
public:
	WinShapesRenderer(void);
	~WinShapesRenderer(void);

	void DrawHealthyBunny(HealthyBunny *healthyBunny);
	void DrawPlayer(Player *player);
};

