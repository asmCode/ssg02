#pragma once

#include "IBunnyState.h"
#include <GenericSingleton.h>

class Player;
class IBunny;

class SettingsInRanks : public IBunnyState, public GenericSingleton<SettingsInRanks>
{
	friend class GenericSingleton<SettingsInRanks>;

public:
	void Update(IBunny *bunny, float time, float seconds);
	IBunnyState::State GetStateType() const;

	void Initialize(Player *player);

private:
	SettingsInRanks();
	~SettingsInRanks(void);

	void Enter();
	void Leave();

	Player *m_player;
};

