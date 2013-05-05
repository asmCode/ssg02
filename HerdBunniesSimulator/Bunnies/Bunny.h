#pragma once

#include "IBunny.h"

class Model;
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

	// time when hip sub animation starts and ends in m_fuckAnim animation. Those values are stored
	// as a Custom Properties in m_bunnyModel model.
	float m_fuckAnimStart;
	float m_fuckAnimEnd;

	float m_currentAnimTime;
	Animation *m_currentAnim;
	Model *m_currentModel;

	void InitFuckAnimBounds(Model *model);
	virtual void Draw(float time, float seconds);

private:
	float m_moveAnimProgress;

	float m_delayTime;
	float m_jumpDistance;
};

