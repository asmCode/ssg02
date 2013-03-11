#pragma once

#include "IBunnyState.h"
#include <Core/GenericSingleton.h>

class IBunny;

class Fucking : public IBunnyState, public GenericSingleton<Fucking>
{
	friend class GenericSingleton<Fucking>;

public:
	void Update(IBunny *bunny, float time, float seconds);
	IBunnyState::State GetStateType() const;

private:
	Fucking(void);
	~Fucking(void);

	void Enter(IBunny *bunny);
	void Leave(IBunny *bunny);
};

