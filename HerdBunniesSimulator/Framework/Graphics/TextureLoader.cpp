#include "TextureLoader.h"

#include "Texture.h"
#include "PngLoader.h"

Texture* TextureLoader::Load(const std::string &path)
{
	int width, height, bpp;
	BYTE *data;
	PngLoader::LoadImage(path.c_str(), width, height, bpp, data);

	Texture *texture = new Texture(width, height, bpp, data, Texture::Wrap_Repeat, Texture::Filter_LinearMipmapLinear, Texture::Filter_Linear, true);
	PngLoader::ReleaseData(data);
	return texture;
}

