#pragma once

#include "Vertex.h"
#include "Material.h"

#include <string>

class Mesh;
class BoundingBox;
class BoundingSphere;

class MeshPart
{
public:
	unsigned int vboId;
	unsigned int m_vertexArrayId;
	Material *material;

	int		m_verticesCount;
	Vertex	*m_vertices;
	Mesh	*m_mesh;

	BoundingBox		*m_bbox;
	BoundingSphere	*m_bsphere;
	
	bool visible;
	bool isAlwaysVisible;

public:
	std::string materialName;

	MeshPart(int verticesCount, Vertex *vertices, Mesh *mesh);
	~MeshPart();

	void SetMaterial(Material *material);
	Material *GetMaterial();

	int GetVerticesCount();
	const Vertex* GetVertices();
	void SetVisibility(bool visible);
	bool IsVisible() const;
	bool& IsAlvaysVisible();

	void Draw();
};
