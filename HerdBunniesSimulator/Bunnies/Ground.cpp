#include "Ground.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"

#include <Graphics/Model.h>
#include <Graphics/Texture.h>
#include <Graphics/Content/Content.h>
#include <GL/glew.h>
#include <assert.h>

#include "SparksGenerator.h"
#include "ParticleRenderer.h"

SparksGenerator *a;
ParticleRenderer *b;

Ground::Ground()
{
	b = new ParticleRenderer();
	a = new SparksGenerator(200, b, NULL);

	m_groundModel = InterfaceProvider::GetContent()->Get<Model>("ground");
	assert(m_groundModel != NULL);

	m_grassX1Model = InterfaceProvider::GetContent()->Get<Model>("grass_x1");
	assert(m_grassX1Model != NULL);

	m_colorMapTex = InterfaceProvider::GetContent()->Get<Texture>("grass_color_map");
	assert(m_colorMapTex != NULL);
}

Ground::~Ground()
{
}

void Ground::Update(float time, float seconds)
{
	a->Update(seconds);
}

void Ground::Draw(float time, float seconds)
{
	a->Draw(seconds, sm::Matrix::IdentityMatrix(), m_viewMatrix);

	DrawingRoutines::DrawCelShaded(m_groundModel, m_viewMatrix, sm::Matrix::IdentityMatrix());

	//glDepthMask(GL_FALSE);
	//glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	DrawingRoutines::DrawGrass(m_grassX1Model, m_colorMapTex, m_viewMatrix, sm::Matrix::IdentityMatrix());
	glDisable(GL_ALPHA_TEST);
	//glDisable(GL_BLEND);
	//glDepthMask(GL_TRUE);
}

void Ground::SetViewMatrix(const sm::Matrix &viewMatrix)
{
	m_viewMatrix = viewMatrix;
}

