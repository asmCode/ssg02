#pragma once

#include <Math/Vec3.h>
#include <vector>
#include <stdint.h>

class HealthyBunny;
class BadBunny;
class IBunny;
class IShapesRenderer;

class BunniesManager
{
public:
	BunniesManager(IShapesRenderer *shapesRenderer);
	~BunniesManager(void);

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

	void ClearBunnies();
	void ResetForNewGame(uint32_t healthyBunniesCount);

	bool CheckCollision(const IBunny *bunny);
	bool CheckCollision(const sm::Vec3 &position, float radius, const IBunny *excludeFromTest);

private:
	static const uint16_t MaxBunniesCount = 100;

	IShapesRenderer *m_shapesRenderer;

	HealthyBunny *m_healthyBunnies[MaxBunniesCount];
	BadBunny *m_badBunnies[MaxBunniesCount];

	float m_reproduceColldown;
	float m_reproduceDelay;

	bool ShouldGoToReproduce();
	void GoToReproduce();
};

