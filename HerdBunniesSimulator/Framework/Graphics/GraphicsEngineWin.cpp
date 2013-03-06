#include "GraphicsEngineWin.h"
#include "ImageLoader.h"
#include "Texture.h"

GraphicsEngineWin::GraphicsEngineWin(void)
{
}

GraphicsEngineWin::~GraphicsEngineWin(void)
{
}

Texture* GraphicsEngineWin::Loadtexture(const std::string &path)
{
	uint8_t *data;
	uint32_t width;
	uint32_t height;
	uint32_t bytesCount;

	if (!ImageLoader::LoadFromFile(path, data, width, height, bytesCount))
		return NULL;

	Texture *texture = new Texture(
		width,
		height,
		bytesCount * 8,
		data,
		Texture::Wrap_ClampToEdge,
		Texture::Filter_Nearest,
		Texture::Filter_Nearest,
		false);

	return texture;
}

//void GraphicsEngineWin::DrawImage(Image *image, float x, float y)
//{
//	//image-
//}
//
