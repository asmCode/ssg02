#ifndef _SHAPES_RENDERER_
#define _SHAPES_RENDERER_

class HealthyBunny;
class BadBunny;
class Player;

class IShapesRenderer
{
public:
	virtual void DrawHealthyBunny(HealthyBunny *healthyBunny) = 0;
	virtual void DrawPlayer(Player *player) = 0;
};

#endif

