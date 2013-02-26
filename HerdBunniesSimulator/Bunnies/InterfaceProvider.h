#pragma once

class IShapesRenderer;
class IGraphicsEngine;

class InterfaceProvider
{
	friend class GameController;

public:
	static IShapesRenderer* GetShapesRenderer();
	static IGraphicsEngine* GetGraphicsEngine();

private:
	static IShapesRenderer *m_shapesRenderer;
	static IGraphicsEngine *m_graphicsEngine;
};

