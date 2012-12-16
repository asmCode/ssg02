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
		State_RestingAfterFucking,
		State_BeeingFucked,
		State_RunningAway,
		State_ChangingToInfected,
		State_Dying,
	};

	virtual ~IBunnyState() {}

	virtual void Enter(IBunny *bunny) {}
	virtual void Leave(IBunny *bunny) {}

	virtual void Update(IBunny *bunny, float time, float seconds) = 0;
	virtual State GetStateType() const = 0;
};

#endif

