#pragma once

#include "MeshPart.h"
#include "../Math/Matrix.h"
#include <vector>
#include <string>

#include <Windows.h>
#include <GL/glew.h>
#include <gl/gl.h>

class Mesh
{
private:
	std::vector<MeshPart*> meshParts;
	sm::Matrix transform;

public:
	int id;
	std::string name;

	Mesh();
	~Mesh();

	void AddMeshPart(MeshPart *meshPart);
	std::vector<MeshPart*>& GetMeshParts();

	bool IsCam();
	int GetId();
	sm::Matrix& Transform();

	sm::Vec3 colorMask;
};
