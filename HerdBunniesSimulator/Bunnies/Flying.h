#pragma once

#include "IBunnyState.h"
#include <Core/GenericSingleton.h>

class IBunny;

class Flying : public IBunnyState, public GenericSingleton<Flying>
{
	friend class GenericSingleton<Flying>;

public:
	void Update(IBunny *bunny, float time, float seconds);
	IBunnyState::State GetStateType() const;

private:
	Flying(void);
	~Flying(void);

	void Enter(IBunny *bunny);
	void Leave(IBunny *bunny);
};

