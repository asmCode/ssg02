#ifndef _IBUNNY_STATE_
#define _IBUNNY_STATE_

class IBunny;

class IBunnyState
{
public:
	enum State
	{
		State_Idle,
		State_SettingInRank,
		State_GoingToReproduction,
		State_Reproducting,
		State_Respawning,
		State_Hunting,
		State_Fucking,
		State_RestingAfterFucking
	};

	virtual ~IBunnyState() {}

	virtual void Enter() {}
	virtual void Leave() {}

	virtual void Update(IBunny *bunny, float time, float seconds) = 0;
	virtual State GetStateType() const = 0;
};

#endif

