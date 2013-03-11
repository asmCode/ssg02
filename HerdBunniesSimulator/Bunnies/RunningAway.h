#pragma once

#include "IBunnyState.h"
#include <Core/GenericSingleton.h>

class IBunny;
class BunniesManager;

class RunningAway : public IBunnyState, public GenericSingleton<RunningAway>
{
	friend class GenericSingleton<RunningAway>;

public:
	void Update(IBunny *bunny, float time, float seconds);
	IBunnyState::State GetStateType() const;
	void Initialize(BunniesManager *bunniesManager);

private:
	BunniesManager *m_bunniesManager;

	RunningAway(void);
	~RunningAway(void);

	void Enter(IBunny *bunny);
	void Leave(IBunny *bunny);
};

