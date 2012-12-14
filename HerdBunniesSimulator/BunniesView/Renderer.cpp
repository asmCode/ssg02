#include "Renderer.h"

#include "Shapes.h"

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <time.h>
#include "../Bunnies/Player.h"
#include "IShapesRenderer.h"
#include "WinShapesRenderer.h"
#include "../Bunnies/BunniesManager.h"
#include "../Bunnies/Idle.h"
#include "../Bunnies/SettingsInRanks.h"
#include "../Bunnies/Reproducting.h"
#include "../Bunnies/Respawning.h"
#include "../Bunnies/RestingAfterFucking.h"

Player *player;
IShapesRenderer *shapesRenderer;
BunniesManager *bunniesMgr;

Renderer::Renderer(OpenglWindow *glwnd)
{
	this ->glwnd = glwnd;
	input = new Input(glwnd ->GetHwnd());
}

void Renderer::Initialize()
{
	srand(time(NULL));

	input ->RegisterObserver(this);

	shapesRenderer = new WinShapesRenderer();

	player = new Player(shapesRenderer);
	bunniesMgr = new BunniesManager(shapesRenderer);
	bunniesMgr->ResetForNewGame(2);

	Idle::GetInstance()->Initialize(player);
	SettingsInRanks::GetInstance()->Initialize(player, bunniesMgr);
	Reproducting::GetInstance()->Initialize(player, bunniesMgr);
	Respawning::GetInstance()->Initialize(bunniesMgr);
	RestingAfterFucking::GetInstance()->Initialize(bunniesMgr);
}

void Renderer::KeyDown(int keyCode)
{
	if (keyCode == VK_SPACE)
		scale = 2.0f;

	switch (keyCode)
	{
	case 'W':
		player->SetForwadMove(-1.0f);
		break;

	case 'S':
		player->SetForwadMove(1.0f);
		break;

	case 'A':
		player->SetStrafeMove(-1.0f);
		break;

	case 'D':
		player->SetStrafeMove(1.0f);
		break;
	}
}

void Renderer::KeyUp(int keyCode)
{
	if (keyCode == VK_SPACE)
		scale = 1.0f;

	switch (keyCode)
	{
	case 'W':
		player->SetForwadMove(0.0f);
		break;

	case 'S':
		player->SetForwadMove(0.0f);
		break;

	case 'A':
		player->SetStrafeMove(0.0f);
		break;

	case 'D':
		player->SetStrafeMove(0.0f);
		break;
	}
}

void Renderer::MouseMove(int x, int y, int xShift, int yShift)
{
	double modelView[16];
	double projMatrix[16];
	int viewport[4];

	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);

	double dx, dy, dz;
	
	gluUnProject(x, y, 0.0, modelView, projMatrix, viewport, &dx, &dy, &dz);

	sm::Vec3 pos = player->GetPosition();
	sm::Vec3 trg = (sm::Vec3(dx, 0.0f, -dy) - pos).GetNormalized();
	
	player->SetLookTarget(trg);
}

void Renderer::Update(float time, float seconds)
{
	input->UpdateMouse();
	input->Update();

	player->Update(time, seconds);
	bunniesMgr->Update(time, seconds);
}

void Renderer::Render(float time, float seconds)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	player->Draw(time, seconds);
	bunniesMgr->Draw(time, seconds);

	glwnd ->SwapBuffers();
}

