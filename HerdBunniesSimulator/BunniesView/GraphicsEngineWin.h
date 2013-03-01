#pragma once

#include "../Bunnies/IGraphicsEngine.h"

class GraphicsEngineWin : public IGraphicsEngine
{
public:
	GraphicsEngineWin(void);
	~GraphicsEngineWin(void);

	ITexture* Loadtexture(const std::string &path); 

	void DrawImage(Image *image, float x, float y);
};

