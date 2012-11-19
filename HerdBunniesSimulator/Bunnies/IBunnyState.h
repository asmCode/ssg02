#ifndef _IBUNNY_STATE_
#define _IBUNNY_STATE_

class IBunny;

class IBunnyState
{
public:
	enum State
	{
		State_DoNothing,
		State_GoToFarmer,
	};

	virtual ~IBunnyState() {}

	virtual void Enter() {}
	virtual void Leave() {}

	virtual void Update(IBunny *bunny, float time, float seconds) = 0;
	virtual State GetStateType() const = 0;
};

#endif

