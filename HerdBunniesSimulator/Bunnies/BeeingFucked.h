#pragma once

#include "IBunnyState.h"
#include <GenericSingleton.h>

class IBunny;
class Player;
class BunniesManager;

class BeeingFucked : public IBunnyState, public GenericSingleton<BeeingFucked>
{
	friend class GenericSingleton<BeeingFucked>;

public:
	void Update(IBunny *bunny, float time, float seconds);
	IBunnyState::State GetStateType() const;

	void Initialize(BunniesManager *bunniesManager);

private:
	BeeingFucked(void);
	~BeeingFucked(void);

	void Enter(IBunny *bunny);
	void Leave(IBunny *bunny);

	BunniesManager *m_bunniesManager;
};

