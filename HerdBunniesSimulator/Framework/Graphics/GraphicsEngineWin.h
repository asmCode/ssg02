#ifndef GRAPHICS_ENGINE_WIN
#define GRAPHICS_ENGINE_WIN

#include "IGraphicsEngine.h"

class GraphicsEngineWin : public IGraphicsEngine
{
public:
	GraphicsEngineWin(void);
	~GraphicsEngineWin(void);

	Texture* Loadtexture(const std::string &path); 

	//void DrawImage(Image *image, float x, float y);
};

#endif // GRAPHICS_ENGINE_WIN

