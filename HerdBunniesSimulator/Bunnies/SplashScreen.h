#pragma once

#include "IScreen.h"
#include <Graphics/Texture.h>

class SplashScreen : public IScreen
{
public:
	SplashScreen(void);
	~SplashScreen(void);

	bool InitResources();
	bool ReleaseResources();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

private:
//	Tex
};

