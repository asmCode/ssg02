#include "ParticleRenderer.h"
#include "Spark.h"
#include "DrawingRoutines.h"

void ParticleRenderer::Draw(Spark *spark, const sm::Matrix &viewMatrix)
{
	sm::Matrix worldMatrix = sm::Matrix::TranslateMatrix(spark->m_throw.GetPosition());

	DrawingRoutines::DrawBloodParticle(viewMatrix, worldMatrix);
}

