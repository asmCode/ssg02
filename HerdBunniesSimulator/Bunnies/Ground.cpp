#include "Ground.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include <Graphics/Model.h>
#include <Graphics/Content/Content.h>
#include <assert.h>

Ground::Ground()
{
	m_groundModel = InterfaceProvider::GetContent()->Get<Model>("ground");
	assert(m_groundModel != NULL);
}

Ground::~Ground()
{
}

void Ground::Update(float time, float seconds)
{
}

void Ground::Draw(float time, float seconds)
{
	DrawingRoutines::DrawCelShaded(m_groundModel, m_viewMatrix, sm::Matrix::IdentityMatrix());
}

void Ground::SetViewMatrix(const sm::Matrix &viewMatrix)
{
	m_viewMatrix = viewMatrix;
}

