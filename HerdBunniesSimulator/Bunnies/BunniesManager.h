#pragma once

#include <Math/Vec3.h>
#include <Math/Matrix.h>
#include <vector>
#include <stdint.h>

class IBunny;
class HealthyBunny;
class InfectedBunny;

class BunniesManager
{
public:
	static const uint16_t MaxBunniesCount = 100;

	BunniesManager();
	~BunniesManager(void);

	void Update(float time, float seconds);
	void Draw(float time, float seconds, const sm::Matrix &viewMatrix);

	void ClearBunnies();
	void ResetForNewGame(uint32_t healthyBunniesCount);
	void BornNewRabbit(const sm::Vec3 &position);

	bool CheckCollision(const IBunny *bunny);
	bool CheckCollision(const sm::Vec3 &position, float radius, const IBunny *excludeFromTest);

	void SpawnInfectedBunny();
	void ChangeToInfected(HealthyBunny *hbunny);

	HealthyBunny *GetRandomHealthyBunny(
		bool ableToReproduce = false,
		bool ableToFuck = false,
		const IBunny *excludeFromTest = NULL);

	InfectedBunny* GetUnusedInfectedBunny();

	HealthyBunny** GetHealthyBunnies();
	InfectedBunny** GetInfectedBunnies();

private:
	HealthyBunny *m_healthyBunnies[MaxBunniesCount];
	InfectedBunny *m_infectedBunnies[MaxBunniesCount];

	float m_reproduceColldown;
	float m_spawnCooldown;

	uint32_t m_maxHealthyBunnyIndex;

	bool ShouldGoToReproduce();
	void GoToReproduce();

	bool ShouldRespawnInfectedBunny();

	sm::Vec3 GetRandomRespawnPosition();
};

