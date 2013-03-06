#ifndef CONTENT
#define CONTENT

#include <string>
#include <map>
#include <assert.h>

class IGraphicsEngine;
class Texture;

class Content
{
public:
	Content(IGraphicsEngine *graphicsEngine);
	~Content();

	void LoadTextures(const std::string &fullPath);

	template <typename T>
	T* Get(const std::string &name)
	{
		std::map<std::string, T*> &resourcesMap = GetContentMap<T>();
		std::map<std::string, T*>::iterator it = resourcesMap.find(name);
		if (it == resourcesMap.end())
			return NULL;

		return it->second;
	}

private:
	IGraphicsEngine *m_graphicsEngine;

	std::map<std::string, Texture*> m_textures;

	template <typename T>
	std::map<std::string, T*>& GetContentMap()
	{
		assert(false);

		return m_textures; // just to hide warning
	}

	template <>
	std::map<std::string, Texture*>& GetContentMap<Texture>()
	{
		return m_textures;
	}
};

#endif // CONTENT


