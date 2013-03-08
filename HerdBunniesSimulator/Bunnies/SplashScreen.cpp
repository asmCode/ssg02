#include "SplashScreen.h"
#include "InterfaceProvider.h"
#include <Graphics/Content/Content.h>
#include <Graphics/SpriteBatch.h>

SplashScreen::SplashScreen(void) :
	m_splashScreenTex(NULL)
{
}


SplashScreen::~SplashScreen(void)
{
}

bool SplashScreen::InitResources()
{
	m_splashScreenTex = InterfaceProvider::GetContent()->Get<Texture>("SplashScreen");

	return true;
}

bool SplashScreen::ReleaseResources()
{
	return true;
}

void SplashScreen::Draw(float time, float seconds)
{
	InterfaceProvider::GetSpriteBatch()->Begin();
	InterfaceProvider::GetSpriteBatch()->Draw(m_splashScreenTex, 0, 0);
	InterfaceProvider::GetSpriteBatch()->End();
}

void SplashScreen::Update(float time, float seconds)
{
}

