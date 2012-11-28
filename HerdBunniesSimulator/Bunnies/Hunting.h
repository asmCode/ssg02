#pragma once

#include "IBunnyState.h"
#include <GenericSingleton.h>

class IBunny;

class Hunting : public IBunnyState, public GenericSingleton<Hunting>
{
	friend class GenericSingleton<Hunting>;

public:
	void Update(IBunny *bunny, float time, float seconds);
	IBunnyState::State GetStateType() const;

private:
	Hunting(void);
	~Hunting(void);

	void Enter();
	void Leave();
};

