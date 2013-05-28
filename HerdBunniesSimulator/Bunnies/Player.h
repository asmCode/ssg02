#pragma once

#include <Math/Vec3.h>
#include <Math/Matrix.h>

class IShapesRenderer;
class Model;
class Animation;

class Player
{
public:
	Player();
	~Player(void);

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

	void SetLookTarget(const sm::Vec3 &lookTarget);
	void SetForwardMove(float forwardMove);
	void SetStrafeMove(float strafeMove);

	const sm::Vec3& GetPosition() const;
	const sm::Vec3& GetLookTarget() const;
	sm::Vec3 GetEyePosition() const;

	sm::Matrix GetViewMatrix() const;

	void Kick();
	bool IsKicking() const;
	bool IsAbleToKick() const;

private:
	sm::Vec3 m_position;
	sm::Vec3 m_lookTarget;

	float m_forwardMove;
	float m_strafeMove;

	Model *m_leg;
	Animation *m_kickAnim;

	float m_kickProgress;
	bool m_isKicking;
	float m_kickCooldown;
};

