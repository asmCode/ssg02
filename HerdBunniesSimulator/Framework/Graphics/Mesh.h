#pragma once

#include "ITransformable.h"
#include <Math\Matrix.h>

#include <vector>
#include <map>
#include <string>

class MeshPart;
class Property;

class Mesh : public ITransformable
{
	friend class ModelLoader;

public:
	int id;
	std::string name;
	sm::Matrix m_worldInverseMatrix;
	sm::Matrix m_worldMatrix;

	Mesh();
	~Mesh();

	void AddMeshPart(MeshPart *meshPart);
	std::vector<MeshPart*>& GetMeshParts();

	Property* FindProperty(const std::string &name);

	bool IsCam();
	int GetId();
	sm::Matrix& Transform();
	sm::Matrix& AnimTransform();

	sm::Vec3 colorMask;

	Mesh *CreateReference();

private:
	std::vector<MeshPart*> meshParts;
	sm::Matrix transform;
	sm::Matrix animTransform;

	std::map<std::string, Property*> m_properties;
};
