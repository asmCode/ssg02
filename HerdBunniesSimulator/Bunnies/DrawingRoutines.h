#ifndef DRAWING_ROUTINES
#define DRAWING_ROUTINES

#include <Math/Vec3.h>
#include <Math/Matrix.h>

class Shader;
class Model;
class Texture;

class DrawingRoutines
{
public:
	static bool Initialize();

	static void DrawCelShaded(Model *model, const sm::Matrix &viewMatrix, sm::Matrix &worldMatrix);

	static void SetLightPosition(const sm::Vec3 &lightPosition);
	static void SetOutlineWidth(float outlineWidth);
	static void SetProjectionMatrix(const sm::Matrix &projMatrix);

private:
	static Shader *m_celShadingShader;
	static Shader *m_outlineShader;

	static float m_outlineWidth;
	static sm::Vec3 m_lightPosition;
	static sm::Matrix m_projMatrix;
	static Texture *m_celLightTex;
};

#endif // DRAWING_ROUTINES

