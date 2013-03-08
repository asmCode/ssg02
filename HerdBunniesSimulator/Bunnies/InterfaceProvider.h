#pragma once

class IShapesRenderer;
class IGraphicsEngine;
class Content;
class SpriteBatch;

class InterfaceProvider
{
	friend class GameController;

public:
	static IShapesRenderer* GetShapesRenderer();
	static IGraphicsEngine* GetGraphicsEngine();
	static Content* GetContent();
	static SpriteBatch* GetSpriteBatch();

private:
	static IShapesRenderer *m_shapesRenderer;
	static IGraphicsEngine *m_graphicsEngine;
	static Content *m_content;
	static SpriteBatch *m_spriteBatch;
};

