#include "Renderer.h"
#include "Shapes.h"

#include "../Bunnies/InfectedBunniesFactory.h"
#include "../Bunnies/Player.h"

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <time.h>
#include <assert.h>
#include <Graphics/IGraphicsEngine.h>
#include <Graphics/GraphicsEngineFactory.h>

IGameController *gctrl;
IGraphicsEngine *graphics;

bool mouseDown = false;

Renderer::Renderer(OpenglWindow *glwnd)
{
	this ->glwnd = glwnd;
	input = new Input(glwnd ->GetHwnd());
}

void Renderer::Initialize()
{
	char currentDir[MAX_PATH + 1];
	GetCurrentDirectory(MAX_PATH + 1, currentDir);

	srand(time(NULL));

	input ->RegisterObserver(this);

	graphics = GraphicsEngineFactory::Create();

	gctrl = InfectedBunniesFactory::Create(graphics);
	bool success = gctrl->Initialize(currentDir);
	assert(success != NULL);
}

void Renderer::KeyDown(int keyCode)
{
	if (keyCode == VK_SPACE)
		scale = 2.0f;

	switch (keyCode)
	{
	case 'W':
		gctrl->proto_SetForwardMove(-1.0f);
		break;

	case 'S':
		gctrl->proto_SetForwardMove(1.0f);
		break;

	case 'A':
		gctrl->proto_SetStrafeMove(-1.0f);
		break;

	case 'D':
		gctrl->proto_SetStrafeMove(1.0f);
		break;

	case VK_LBUTTON:
		{
			mouseDown = true;
			POINT p;
			GetCursorPos(&p);
			gctrl->HandlePress(0, sm::Vec2(p.x, p.y));
		}
	}
}

void Renderer::KeyUp(int keyCode)
{
	if (keyCode == VK_SPACE)
		scale = 1.0f;

	switch (keyCode)
	{
	case 'W':
		gctrl->proto_SetForwardMove(0.0f);
		break;

	case 'S':
		gctrl->proto_SetForwardMove(0.0f);
		break;

	case 'A':
		gctrl->proto_SetStrafeMove(0.0f);
		break;

	case 'D':
		gctrl->proto_SetStrafeMove(0.0f);
		break;

	case VK_LBUTTON:
		{
			mouseDown = false;
			POINT p;
			GetCursorPos(&p);
			gctrl->HandleRelease(0, sm::Vec2(p.x, p.y));
		}
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

	Player *player = gctrl->proto_GetPlayer();

	sm::Vec3 pos = player->GetPosition();
	sm::Vec3 trg = (sm::Vec3(dx, 0.0f, -dy) - pos).GetNormalized();
	
	player->SetLookTarget(trg);

	if (mouseDown)
	{
		gctrl->HandleMove(0, sm::Vec2(x, y));
	}
}

void Renderer::Update(float time, float seconds)
{
	input->UpdateMouse();
	input->Update();

	gctrl->Update(time, seconds);
}

void Renderer::Render(float time, float seconds)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gctrl->Draw(time, seconds);

	glwnd ->SwapBuffers();
}

