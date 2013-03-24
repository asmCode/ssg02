#ifndef GROUND
#define GROUND

#include <Math/Matrix.h>

class Model;

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
	sm::Matrix m_viewMatrix;
};

#endif // GROUND

