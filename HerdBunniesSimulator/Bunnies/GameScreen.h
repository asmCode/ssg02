#pragma once

#include "IScreen.h"
#include "IDamageableProvider.h"

class Player;
class IGun;
class IShapesRenderer;
class BunniesManager;

class GameScreen : public IScreen,
				   public IDamageableProvider
{
public:
	GameScreen(void);
	~GameScreen(void);

	bool Initialize();

	bool InitResources();
	bool ReleaseResources();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

	void HandlePress(uint32_t pointIndex, const sm::Vec2 &point);
    void HandleRelease(uint32_t pointIndex, const sm::Vec2 &point);
	void HandleMove(uint32_t pointIndex, const sm::Vec2 &point);

	Player* GetPlayer();

	void GetAllDamageables(IDamageable **objects, uint32_t &count);

	void GetDamageablesInCone(
		IDamageable **objects,
		uint32_t &count,
		const sm::Vec3 &coneTop,
		const sm::Vec3 &coneTarget,
		float cosOfAngle);

	void GetDamageablesInRange(
		IDamageable **objects,
		uint32_t &count,
		const sm::Vec3 &position,
		float range);

private:
	Player *m_player;
	IGun *m_activeGun;
	BunniesManager *m_bunniesMgr;
};

