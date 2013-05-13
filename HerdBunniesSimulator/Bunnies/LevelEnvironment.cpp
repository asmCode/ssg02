#include "LevelEnvironment.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include <Graphics/Model.h>
#include <Graphics/Content/Content.h>
#include <assert.h>

LevelEnvironment::LevelEnvironment()
{
	m_fenceModel = InterfaceProvider::GetContent()->Get<Model>("fence");
	assert(m_fenceModel != NULL);

	m_staticModel = InterfaceProvider::GetContent()->Get<Model>("level_env");
	assert(m_staticModel != NULL);

	m_fieldModel = InterfaceProvider::GetContent()->Get<Model>("field");
	assert(m_fieldModel != NULL);
}

LevelEnvironment::~LevelEnvironment()
{
}

void LevelEnvironment::Update(float time, float seconds)
{
}

void LevelEnvironment::Draw(float time, float seconds)
{
	DrawingRoutines::DrawCelShaded(m_fenceModel, m_viewMatrix, sm::Matrix::IdentityMatrix());
	DrawingRoutines::DrawCelShaded(m_fieldModel, m_viewMatrix, sm::Matrix::IdentityMatrix());
	DrawingRoutines::DrawCelShaded(m_staticModel, m_viewMatrix, sm::Matrix::IdentityMatrix());
}

void LevelEnvironment::SetViewMatrix(const sm::Matrix &viewMatrix)
{
	m_viewMatrix = viewMatrix;
}

