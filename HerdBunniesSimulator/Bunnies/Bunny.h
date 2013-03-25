#pragma once

#include "IBunny.h"

class Bunny : public IBunny
{
public:
	Bunny(void);
	~Bunny(void);

	float GetHealth() const;

	void UpdateMovement(float seconds, float movementSpeed);

	void SetDestinationPosition(const sm::Vec3 &position);

protected:
	float m_health;

	// actual position
	sm::Vec3 m_position;

	// move direction. Only for visualization purpose
	sm::Vec3 m_moveTarget;

	// position which bunny should reach
	sm::Vec3 m_targetPosition;
};

