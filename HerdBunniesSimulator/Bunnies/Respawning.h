#pragma once

#include "IBunnyState.h"
#include <GenericSingleton.h>

class IBunny;
class BunniesManager;

class Respawning : public IBunnyState, public GenericSingleton<Respawning>
{
	friend class GenericSingleton<Respawning>;

public:
	void Update(IBunny *bunny, float time, float seconds);
	IBunnyState::State GetStateType() const;
	void Initialize(BunniesManager *bunniesManager);

private:
	BunniesManager *m_bunniesManager;

	Respawning(void);
	~Respawning(void);

	void Enter();
	void Leave();
};

