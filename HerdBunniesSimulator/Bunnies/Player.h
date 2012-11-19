#pragma once

#include <Math/Vec3.h>

class IShapesRenderer;

class Player
{
public:
	Player(IShapesRenderer *shapesRenderer);
	~Player(void);

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

	void SetLookTarget(const sm::Vec3 &lookTarget);
	void SetForwadMove(float forwardMove);
	void SetStrafeMove(float strafeMove);

	const sm::Vec3& GetPosition() const;
	const sm::Vec3& GetLookTarget() const;

private:
	static const float MoveSpeed;

	IShapesRenderer *m_shapesRenderer;

	sm::Vec3 m_position;
	sm::Vec3 m_lookTarget;

	float m_forwardMove;
	float m_strafeMove;
};

