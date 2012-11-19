#pragma once

#include <vector>
#include <stdint.h>

class HealthyBunny;
class BadBunny;
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

private:
	static const uint16_t MaxBunniesCount = 100;

	IShapesRenderer *m_shapesRenderer;

	HealthyBunny *m_healthyBunnies[MaxBunniesCount];
	BadBunny *m_badBunnies[MaxBunniesCount];
};

