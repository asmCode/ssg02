#pragma once

#include "IBunny.h"

class Animation;

class Bunny : public IBunny
{
	friend class Reproducting;
	friend class GoingToReproduction;
	friend class Hunting;
	friend class RunningAway;

public:
	Bunny(void);
	~Bunny(void);

	float GetHealth() const;

	void UpdateMovement(float seconds, float movementSpeed, float delayBetweenJumps);

	void SetDestinationPosition(const sm::Vec3 &position);

protected:
	float m_health;

	// actual position
	sm::Vec3 m_position;

	// move direction. Only for visualization purpose
	sm::Vec3 m_moveTarget;

	// position which bunny should reach
	sm::Vec3 m_targetPosition;

	float m_currentAnimTime;
	Animation *m_currentAnim;

	virtual void Draw(float time, float seconds);

private:
	float m_moveAnimProgress;

	float m_delayTime;
	float m_jumpDistance;
};

