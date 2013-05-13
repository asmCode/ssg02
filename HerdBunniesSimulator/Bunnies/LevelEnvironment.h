#ifndef LEVEL_ENVIRONMENT
#define LEVEL_ENVIRONMENT

#include <Math/Matrix.h>

class Model;

class LevelEnvironment
{
public:
	LevelEnvironment();
	~LevelEnvironment();

	void SetViewMatrix(const sm::Matrix &viewMatrix);
	void Update(float time, float seconds);
	void Draw(float time, float seconds);

private:
	Model *m_fenceModel;
	Model *m_staticModel;
	Model *m_fieldModel;

	sm::Matrix m_viewMatrix;
};

#endif // LEVEL_ENVIRONMENT

