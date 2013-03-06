#ifndef IGRAPHICS_ENGINE
#define IGRAPHICS_ENGINE

#include <string>

class Texture;

class IGraphicsEngine
{
public:
	virtual ~IGraphicsEngine() {}

	virtual Texture* Loadtexture(const std::string &path) = 0;
};

#endif // IGRAPHICS_ENGINE

