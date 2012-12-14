#pragma once

#include "IBunnyState.h"
#include <GenericSingleton.h>

class IBunny;
class BunniesManager;

class RestingAfterFucking : public IBunnyState, public GenericSingleton<RestingAfterFucking>
{
	friend class GenericSingleton<RestingAfterFucking>;

public:
	void Update(IBunny *bunny, float time, float seconds);
	IBunnyState::State GetStateType() const;
	void Initialize(BunniesManager *bunniesManager);

private:
	BunniesManager *m_bunniesManager;

	RestingAfterFucking(void);
	~RestingAfterFucking(void);

	void Enter();
	void Leave();
};

