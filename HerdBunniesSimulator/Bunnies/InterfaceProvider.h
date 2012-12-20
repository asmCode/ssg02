#pragma once

class IShapesRenderer;

class InterfaceProvider
{
	friend class GameController;

public:
	static IShapesRenderer* GetShapesRenderer();

private:
	static IShapesRenderer *m_shapesRenderer;
};

