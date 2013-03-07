#pragma once

class IShapesRenderer;
class IGraphicsEngine;
class Content;

class InterfaceProvider
{
	friend class GameController;

public:
	static IShapesRenderer* GetShapesRenderer();
	static IGraphicsEngine* GetGraphicsEngine();
	static Content* GetContent();

private:
	static IShapesRenderer *m_shapesRenderer;
	static IGraphicsEngine *m_graphicsEngine;
	static Content *m_content;
};

