#pragma once

#include "IBunnyState.h"
#include <GenericSingleton.h>

class IBunny;
class Player;
class BunniesManager;

class Reproducting : public IBunnyState, public GenericSingleton<Reproducting>
{
	friend class GenericSingleton<Reproducting>;

public:
	void Update(IBunny *bunny, float time, float seconds);
	IBunnyState::State GetStateType() const;

	void Initialize(Player *player, BunniesManager *bunniesManager);

private:
	Reproducting(void);
	~Reproducting(void);

	void Enter(IBunny *bunny);
	void Leave(IBunny *bunny);

	Player *m_player;
	BunniesManager *m_bunniesManager;
};

