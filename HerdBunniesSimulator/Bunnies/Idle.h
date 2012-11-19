#pragma once

#include "IBunnyState.h"
#include <GenericSingleton.h>

class IBunny;
class Player;

class Idle : public IBunnyState, public GenericSingleton<Idle>
{
	friend class GenericSingleton<Idle>;

public:
	void Update(IBunny *bunny, float time, float seconds);
	IBunnyState::State GetStateType() const;

	void Initialize(Player *player);

private:
	Idle();
	~Idle();

	void Enter();
	void Leave();

	bool CheckRunningAway(IBunny *bunny, float time, float seconds);
	bool CheckGoingToReproduction(IBunny *bunny, float time, float seconds);
	bool CheckSettingInRanks(IBunny *bunny, float time, float seconds);
	void DoIdleStuff(IBunny *bunny, float time, float seconds);

	Player *m_player;
};

