#include "InterfaceProvider.h"
#include <stddef.h>
#include <assert.h>

IShapesRenderer *InterfaceProvider::m_shapesRenderer;
IGraphicsEngine *InterfaceProvider::m_graphicsEngine;
Content *InterfaceProvider::m_content;

IShapesRenderer* InterfaceProvider::GetShapesRenderer()
{
	assert(m_shapesRenderer != NULL);
	return m_shapesRenderer;
}

IGraphicsEngine* InterfaceProvider::GetGraphicsEngine()
{
	assert(m_graphicsEngine != NULL);
	return m_graphicsEngine;
}

Content* InterfaceProvider::GetContent()
{
	return m_content;
}

