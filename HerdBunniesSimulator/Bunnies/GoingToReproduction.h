#pragma once

#include "IBunnyState.h"
#include <GenericSingleton.h>

class IBunny;
class Player;

class GoingToReproduction : public IBunnyState, public GenericSingleton<GoingToReproduction>
{
	friend class GenericSingleton<GoingToReproduction>;

public:
	void Update(IBunny *bunny, float time, float seconds);
	IBunnyState::State GetStateType() const;

private:
	GoingToReproduction(void);
	~GoingToReproduction(void);

	void Enter();
	void Leave();

	Player *m_player;
};

