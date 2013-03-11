#pragma once

#include "IBunnyState.h"
#include <Core/GenericSingleton.h>

class Player;
class BunniesManager;
class IBunny;

class SettingsInRanks : public IBunnyState, public GenericSingleton<SettingsInRanks>
{
	friend class GenericSingleton<SettingsInRanks>;

public:
	void Update(IBunny *bunny, float time, float seconds);
	IBunnyState::State GetStateType() const;

	void Initialize(Player *player,
					BunniesManager *bunniesManager);

private:
	SettingsInRanks();
	~SettingsInRanks(void);

	void Enter(IBunny *bunny);
	void Leave(IBunny *bunny);

	Player *m_player;
	BunniesManager *m_bunniesManager;
};

