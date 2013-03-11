#pragma once

#include "IBunnyState.h"
#include <Core/GenericSingleton.h>

class IBunny;
class Player;
class BunniesManager;

class Dying : public IBunnyState, public GenericSingleton<Dying>
{
	friend class GenericSingleton<Dying>;

public:
	void Update(IBunny *bunny, float time, float seconds);
	IBunnyState::State GetStateType() const;

	void Initialize(BunniesManager *bunniesManager);

private:
	Dying(void);
	~Dying(void);

	void Enter(IBunny *bunny);
	void Leave(IBunny *bunny);

	BunniesManager *m_bunniesManager;
};

