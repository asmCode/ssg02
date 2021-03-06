#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include <Graphics/Content/Content.h>
#include <Graphics/Shader.h>
#include <Graphics/MeshPart.h>
#include <Graphics/Mesh.h>
#include <Graphics/Model.h>
#include <assert.h>

Shader* DrawingRoutines::m_celShadingShader;
Shader* DrawingRoutines::m_celShadingMutatingShader;
Shader* DrawingRoutines::m_outlineShader;
Shader* DrawingRoutines::m_outlineMutatingShader;
Shader* DrawingRoutines::m_skydomeShader;
Shader* DrawingRoutines::m_diffTexShader;
Shader* DrawingRoutines::m_grassShader;
float DrawingRoutines::m_outlineWidth;
sm::Vec3 DrawingRoutines::m_lightPosition;
sm::Matrix DrawingRoutines::m_projMatrix;
Texture* DrawingRoutines::m_celLightTex;
Model *DrawingRoutines::m_bloodParticleModel;

bool DrawingRoutines::Initialize()
{
	m_celShadingShader = InterfaceProvider::GetContent()->Get<Shader>("CelShading");
	assert(m_celShadingShader != NULL);

	m_celShadingMutatingShader = InterfaceProvider::GetContent()->Get<Shader>("CelShadingMutating");
	assert(m_celShadingMutatingShader != NULL);

	m_outlineShader = InterfaceProvider::GetContent()->Get<Shader>("Outline");
	assert(m_outlineShader != NULL);

	m_outlineMutatingShader = InterfaceProvider::GetContent()->Get<Shader>("OutlineMutating");
	assert(m_outlineMutatingShader != NULL);

	m_skydomeShader = InterfaceProvider::GetContent()->Get<Shader>("Skydome");
	assert(m_skydomeShader != NULL);

	m_diffTexShader = InterfaceProvider::GetContent()->Get<Shader>("DiffTex");
	assert(m_diffTexShader != NULL);

	m_grassShader = InterfaceProvider::GetContent()->Get<Shader>("Grass");
	assert(m_grassShader != NULL);

	m_celLightTex = InterfaceProvider::GetContent()->Get<Texture>("cel_light");
	assert(m_celLightTex != NULL);

	m_bloodParticleModel = InterfaceProvider::GetContent()->Get<Model>("blood_particle");
	assert(m_bloodParticleModel != NULL);

	m_celShadingShader->BindVertexChannel(0, "a_position");
	m_celShadingShader->BindVertexChannel(1, "a_normal");
	m_celShadingShader->BindVertexChannel(2, "a_coords");
	m_celShadingShader->LinkProgram();

	m_celShadingMutatingShader->BindVertexChannel(0, "a_position");
	m_celShadingMutatingShader->BindVertexChannel(1, "a_normal");
	m_celShadingMutatingShader->BindVertexChannel(2, "a_coords");
	m_celShadingMutatingShader->LinkProgram();

	m_outlineShader->BindVertexChannel(0, "a_position");
	m_outlineShader->BindVertexChannel(1, "a_normal");
	m_outlineShader->LinkProgram();

	m_outlineMutatingShader->BindVertexChannel(0, "a_position");
	m_outlineMutatingShader->BindVertexChannel(1, "a_normal");
	m_outlineMutatingShader->LinkProgram();

	m_skydomeShader->BindVertexChannel(0, "a_position");
	m_skydomeShader->BindVertexChannel(2, "a_coords");
	m_skydomeShader->LinkProgram();

	m_diffTexShader->BindVertexChannel(0, "a_position");
	m_diffTexShader->BindVertexChannel(2, "a_coords");
	m_diffTexShader->LinkProgram();

	m_grassShader->BindVertexChannel(0, "a_position");
	m_grassShader->BindVertexChannel(2, "a_coords");
	m_grassShader->LinkProgram();

	return true;
}

void DrawingRoutines::DrawCelShaded(Model *model, const sm::Matrix &viewMatrix, const sm::Matrix &worldMatrix)
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

void DrawingRoutines::DrawCelShadedMutating(Model *model,
											const sm::Matrix &viewMatrix,
											const sm::Matrix &worldMatrix,
											float mutatingValue,
											Texture *mutatingTex)
{
	assert(model != NULL);

	std::vector<MeshPart*> meshParts;
	model->GetMeshParts(meshParts);

	glDepthMask(GL_FALSE);
	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(1);
	m_outlineMutatingShader->UseProgram();
	m_outlineMutatingShader->SetParameter("u_outlineWidth", m_outlineWidth);
	m_outlineMutatingShader->SetParameter("u_mutatingValue", mutatingValue);
	for (uint32_t i = 0; i < meshParts.size(); i++)
	{
		m_outlineMutatingShader->SetMatrixParameter("u_mvpMatrix", m_projMatrix * (viewMatrix * (worldMatrix * meshParts[i]->mesh->Transform())));
		meshParts[i]->Draw();
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDepthMask(GL_TRUE);
	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	m_celShadingMutatingShader->UseProgram();
	m_celShadingMutatingShader->SetMatrixParameter("u_viewProjMatrix", m_projMatrix * viewMatrix);
	m_celShadingMutatingShader->SetParameter("u_lightPosition", m_lightPosition);
	m_celShadingMutatingShader->SetTextureParameter("u_celLight", 2, m_celLightTex->GetId());
	m_celShadingMutatingShader->SetTextureParameter("u_diffMutatingTex", 1, mutatingTex->GetId());
	m_celShadingMutatingShader->SetParameter("u_vpr_mutatingValue", mutatingValue);
	m_celShadingMutatingShader->SetParameter("u_fpr_mutatingValue", mutatingValue);
	for (uint32_t i = 0; i < meshParts.size(); i++)
	{
		assert(meshParts[i]->GetMaterial() != NULL);
		assert(meshParts[i]->GetMaterial()->diffuseTex != NULL);

		m_celShadingMutatingShader->SetTextureParameter("u_diffTex", 0, meshParts[i]->GetMaterial()->diffuseTex->GetId());
		m_celShadingMutatingShader->SetMatrixParameter("u_worldMatrix", worldMatrix * meshParts[i]->mesh->Transform());
		meshParts[i]->Draw();
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void DrawingRoutines::DrawSkydome(Model *model, const sm::Matrix &viewMatrix, const sm::Matrix &projMatrix)
{
	assert(model != NULL);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	std::vector<MeshPart*> meshParts;
	model->GetMeshParts(meshParts);

	glDepthMask(GL_FALSE);
	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(2);
	m_skydomeShader->UseProgram();
	m_skydomeShader->SetMatrixParameter("u_viewMatrix", viewMatrix);
	m_skydomeShader->SetMatrixParameter("u_projMatrix", projMatrix);
	for (uint32_t i = 0; i < meshParts.size(); i++)
	{
		m_skydomeShader->SetTextureParameter("u_diffTex", 0, meshParts[i]->GetMaterial()->diffuseTex->GetId());
		meshParts[i]->Draw();
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);

	glDepthMask(GL_TRUE);
}

void DrawingRoutines::DrawSprite(Model *model, const sm::Matrix &viewMatrix, const sm::Matrix &worldMatrix)
{
	assert(model != NULL);

	std::vector<MeshPart*> meshParts;
	model->GetMeshParts(meshParts);

	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(2);
	m_diffTexShader->UseProgram();
	m_diffTexShader->SetMatrixParameter("u_mvpMatrix", m_projMatrix * (viewMatrix * worldMatrix));
	for (uint32_t i = 0; i < meshParts.size(); i++)
	{
		assert(meshParts[i]->GetMaterial() != NULL);
		assert(meshParts[i]->GetMaterial()->diffuseTex != NULL);

		m_diffTexShader->SetTextureParameter("u_diffTex", 0, meshParts[i]->GetMaterial()->diffuseTex->GetId());
		meshParts[i]->Draw();
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}

void DrawingRoutines::DrawGrass(Model *model, Texture *colorMapTex, const sm::Matrix &viewMatrix, const sm::Matrix &worldMatrix)
{
	assert(model != NULL);

	std::vector<MeshPart*> meshParts;
	model->GetMeshParts(meshParts);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
	m_grassShader->UseProgram();
	m_grassShader->SetMatrixParameter("u_worldMatrix", worldMatrix);
	m_grassShader->SetMatrixParameter("u_viewProjMatrix", m_projMatrix * viewMatrix);
	m_grassShader->SetTextureParameter("u_colorMapTex", 1, colorMapTex->GetId());
	for (uint32_t i = 0; i < meshParts.size(); i++)
	{
		assert(meshParts[i]->GetMaterial() != NULL);
		assert(meshParts[i]->GetMaterial()->diffuseTex != NULL);

		m_grassShader->SetTextureParameter("u_diffTex", 0, meshParts[i]->GetMaterial()->diffuseTex->GetId());
		meshParts[i]->Draw();
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}

void DrawingRoutines::DrawBloodParticle(const sm::Matrix &viewMatrix, const sm::Matrix &worldMatrix)
{
	DrawCelShaded(m_bloodParticleModel, viewMatrix, worldMatrix);
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

