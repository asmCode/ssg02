#pragma once

#include <Graphics/Image.h>
#include "../Bunnies/ITexture.h"
#include <string>

class IGraphicsEngine
{
public:
	virtual ITexture* Loadtexture(const std::string &path) = 0; 

	virtual void DrawImage(Image *image, float x, float y) = 0;
};

