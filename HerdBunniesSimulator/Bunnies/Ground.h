#ifndef GROUND
#define GROUND

#include <Math/Matrix.h>

class Model;
class Texture;

class Ground
{
public:
	Ground();
	~Ground();

	void SetViewMatrix(const sm::Matrix &viewMatrix);
	void Update(float time, float seconds);
	void Draw(float time, float seconds);

private:
	Model *m_groundModel;
	Model *m_grassX1Model;
	Texture *m_colorMapTex;

	sm::Matrix m_viewMatrix;
};

#endif // GROUND

