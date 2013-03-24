#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include <Graphics/Content/Content.h>
#include <Graphics/Shader.h>
#include <Graphics/MeshPart.h>
#include <Graphics/Mesh.h>
#include <Graphics/Model.h>
#include <assert.h>

Shader* DrawingRoutines::m_celShadingShader;
Shader* DrawingRoutines::m_outlineShader;
float DrawingRoutines::m_outlineWidth;
sm::Vec3 DrawingRoutines::m_lightPosition;
sm::Matrix DrawingRoutines::m_projMatrix;
Texture* DrawingRoutines::m_celLightTex;

bool DrawingRoutines::Initialize()
{
	m_celShadingShader = InterfaceProvider::GetContent()->Get<Shader>("CelShading");
	assert(m_celShadingShader != NULL);

	m_outlineShader = InterfaceProvider::GetContent()->Get<Shader>("Outline");
	assert(m_outlineShader != NULL);

	m_celLightTex = InterfaceProvider::GetContent()->Get<Texture>("cel_light");
	assert(m_celLightTex != NULL);

	m_celShadingShader->BindVertexChannel(0, "a_position");
	m_celShadingShader->BindVertexChannel(1, "a_normal");
	m_celShadingShader->BindVertexChannel(2, "a_coords");
	m_celShadingShader->LinkProgram();

	m_outlineShader->BindVertexChannel(0, "a_position");
	m_outlineShader->BindVertexChannel(1, "a_normal");
	m_outlineShader->LinkProgram();

	return true;
}

void DrawingRoutines::DrawCelShaded(Model *model, const sm::Matrix &viewMatrix, sm::Matrix &worldMatrix)
{
	assert(model != NULL);

	std::vector<MeshPart*> meshParts;
	model->GetMeshParts(meshParts);

	glDepthMask(GL_FALSE);
	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(1);
	m_outlineShader->UseProgram();
	m_outlineShader->SetParameter("u_outlineWidth", m_outlineWidth);
	for (uint32_t i = 0; i < meshParts.size(); i++)
	{
		m_outlineShader->SetMatrixParameter("u_mvpMatrix", m_projMatrix * (viewMatrix * (worldMatrix * meshParts[i]->mesh->Transform())));
		meshParts[i]->Draw();
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDepthMask(GL_TRUE);
	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	m_celShadingShader->UseProgram();
	m_celShadingShader->SetMatrixParameter("u_viewProjMatrix", m_projMatrix * viewMatrix);
	m_celShadingShader->SetParameter("u_lightPosition", m_lightPosition);
	m_celShadingShader->SetTextureParameter("u_celLight", 1, m_celLightTex->GetId());
	for (uint32_t i = 0; i < meshParts.size(); i++)
	{
		assert(meshParts[i]->GetMaterial() != NULL);
		assert(meshParts[i]->GetMaterial()->diffuseTex != NULL);

		m_celShadingShader->SetTextureParameter("u_diffTex", 0, meshParts[i]->GetMaterial()->diffuseTex->GetId());
		m_celShadingShader->SetMatrixParameter("u_worldMatrix", worldMatrix * meshParts[i]->mesh->Transform());
		meshParts[i]->Draw();
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void DrawingRoutines::SetLightPosition(const sm::Vec3 &lightPosition)
{
	m_lightPosition = lightPosition;
}

void DrawingRoutines::SetOutlineWidth(float outlineWidth)
{
	m_outlineWidth = outlineWidth;
}

void DrawingRoutines::SetProjectionMatrix(const sm::Matrix &projMatrix)
{
	m_projMatrix = projMatrix;
}

