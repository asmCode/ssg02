#include "GraphicsEngineWin.h"
#include "ImageLoader.h"
#include "Texture.h"
#include "Shader.h"
#include <assert.h>

GraphicsEngineWin::GraphicsEngineWin(void)
{
}

GraphicsEngineWin::~GraphicsEngineWin(void)
{
}

Texture* GraphicsEngineWin::LoadTexture(const std::string &path)
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

Shader* GraphicsEngineWin::LoadShader(const std::string &vertexShaderPath,
								      const std::string &fragmentShaderPath)
{
	Shader *shader = Shader::LoadFromFile(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

	return shader;
}

void GraphicsEngineWin::DrawSprite(Texture *texture, uint32_t x, uint32_t y)
{
	assert(texture != NULL);
}

//void GraphicsEngineWin::DrawImage(Image *image, float x, float y)
//{
//	//image-
//}
//
