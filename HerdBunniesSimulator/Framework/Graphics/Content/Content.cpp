#include "Content.h"

#include "../IGraphicsEngine.h"
#include <IO/Path.h>

Content::Content(IGraphicsEngine *graphicsEngine) :
	m_graphicsEngine(graphicsEngine)
{
}

Content::~Content()
{
}

void Content::LoadTextures(const std::string &fullPath)
{
	std::vector<std::string> filesNames;
	Path::GetAllFiles(filesNames, fullPath, "*.png");

	for (uint32_t i = 0 ; i < filesNames.size(); i++)
	{
		Path path(fullPath + filesNames[i]);

		m_textures[path.GetFilename()] = m_graphicsEngine->Loadtexture(path.GetFullPath());
	}
}

