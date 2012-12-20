#include "InterfaceProvider.h"
#include <stddef.h>
#include <assert.h>

IShapesRenderer *InterfaceProvider::m_shapesRenderer;

IShapesRenderer* InterfaceProvider::GetShapesRenderer()
{
	assert(m_shapesRenderer != NULL);
	return m_shapesRenderer;
}

