#pragma once

#include <UI/ITouchObserver.h>
#include "Control.h"
#include "AnimButton.h"

class MainMenuPanel :
	public Control,
	public ITouchObserver
{
private:
	AnimButton *playGameBtn;
	AnimButton *freePlayBtn;
	AnimButton *optionsBtn;
	AnimButton *leaderBtn;	// leaderboard
	AnimButton *achBtn;		// achievements
	
	MainMenuPanel();
	
	void TouchPressed(Control *control, int x, int y);
	void OnDraw(float time, float seconds);
	
public:
	static MainMenuPanel *Create();
};

