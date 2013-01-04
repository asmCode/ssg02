#include <stddef.h>
#include "FontRenderer.h"

#define TIXML_USE_STL
#include "../Utils/Xml/tinyxml.h"
#include "../Utils/Image.h"
#include "../Utils/Utils/Path.h"
#include "SpriteBatch.h"

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

FontRenderer::FontRenderer()
{
}

Texture *FontRenderer::LoadFontBitmap(const std::string &path)
{
	if (!Path::IsFileExists(path.c_str()))
		return NULL;
	
	Image *img = Image::LoadImage(path.c_str());
	if (img == NULL)
		return NULL;
	Texture *texture = new Texture(img ->GetWidth(), img ->GetHeight(), img ->GetBpp(), img ->GetData());
	delete img;
	
	texture ->BindTexture();
	//glGenerateMipmap(GL_TEXTURE_2D);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	return texture;
}

bool FontRenderer::ParseBounds(const std::string &strBounds, sm::Rect<int> &bounds)
{
	int x;
	int y;
	int width;
	int height;
	
	if (sscanf(strBounds.c_str(), "%u;%u;%u;%u", &x, &y, &width, &height) != 4)
		return false;
	
	bounds = sm::Rect<int>(x, y, width, height);
	return true;
}

FontRenderer* FontRenderer::LoadFromFile(const char *path)
{
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile(path))
		return NULL;
	
	const TiXmlElement *rootNode = xmlDoc.RootElement();
	if (rootNode == NULL)
		return NULL;
	
	if (strcmp(rootNode ->Value(), "alphabet") != 0)
		return NULL;
	
	FontLetter texLetters[256];
	
	std::string bmpFilename;
	rootNode ->QueryStringAttribute("bitmap", &bmpFilename);
	if (bmpFilename.empty())
		return NULL;
	
	Path _path(path);
	Texture *tex = LoadFontBitmap(_path.GetPath() + bmpFilename);
	if (tex == NULL)
		return NULL;
	
	const TiXmlNode *child = NULL;
	while((child = rootNode->IterateChildren(child)) != NULL)
	{
		const TiXmlElement *charElement = child ->ToElement();
		if (strcmp(charElement ->Value(), "char") == 0)
		{
			std::string letter;
			std::string bounds;
			if (charElement ->QueryStringAttribute("letter", &letter) != TIXML_SUCCESS ||
				charElement ->QueryStringAttribute("bounds", &bounds) != TIXML_SUCCESS ||
				letter.size() != 1)
				return NULL;
			
			sm::Rect<int> boundsValues;
			if (!ParseBounds(bounds, boundsValues))
				return NULL;
			
			texLetters[letter[0]].Size = sm::Point<int>(boundsValues.Width, boundsValues.Height);
			texLetters[letter[0]].Coords = TexPart(tex, boundsValues);
		}
	}
	
	FontRenderer *fontRenderer = new FontRenderer();
	if (fontRenderer != NULL)
	{
		memcpy(fontRenderer ->texLetters, texLetters, sizeof(FontLetter) * 256);
		fontRenderer ->spriteBatch = new SpriteBatch();
	}
	return fontRenderer;
}

FontRenderer::~FontRenderer()
{
}

void FontRenderer::DrawString(const char *text, unsigned x, unsigned y, const Color &color)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	spriteBatch ->Begin();
	unsigned xShift = x;
	unsigned yShift = y;
	unsigned rowHeight = texLetters['A'].Size.Y;
	for (unsigned i = 0; i < strlen(text); i++)
	{
		if (text[i] == '\n')
		{
			yShift += rowHeight;
			xShift = x;
			continue;
		}
		
		FontLetter letter = texLetters[text[i]];
		spriteBatch ->Draw(letter.Coords, color, xShift, yShift);//, letter.Size.X, letter.Size.Y);
		xShift += letter.Size.X;
		
	}
	//spriteBatch ->Draw(texLetters[text[0]].Coords.Tex, Color(255, 0, 0), 0, 40);
	spriteBatch ->End();
}

sm::Point<int> FontRenderer::MeasureString(const char *text)
{
	sm::Point<int> size(0, texLetters['A'].Size.Y);
	
	for (int i = 0; i < strlen(text); i++)
		size.X += texLetters[text[i]].Size.X;
	
	return size;
}
