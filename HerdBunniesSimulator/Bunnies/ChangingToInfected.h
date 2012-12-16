#pragma once

#include "IBunnyState.h"
#include <GenericSingleton.h>

class IBunny;
class BunniesManager;

class ChangingToInfected : public IBunnyState, public GenericSingleton<ChangingToInfected>
{
	friend class GenericSingleton<ChangingToInfected>;

public:
	void Update(IBunny *bunny, float time, float seconds);
	IBunnyState::State GetStateType() const;
	void Initialize(BunniesManager *bunniesManager);

private:
	BunniesManager *m_bunniesManager;

	ChangingToInfected(void);
	~ChangingToInfected(void);

	void Enter(IBunny *bunny);
	void Leave(IBunny *bunny);
};

