#ifndef _INFECTED_BUNNY_
#define _INFECTED_BUNNY_

#include "Bunny.h"
#include "Ticker.h"
#include "ThrowTrajectory.h"
#include <Math/Matrix.h>

class Model;
class IBunnyState;
class HealthyBunny;
class Animation;
class SparksGenerator;

class InfectedBunny : public Bunny
{
	friend class RestingAfterFucking;
	friend class Hunting;
	friend class Fucking;
	friend class Flying;
	friend class Dying;

public:
	InfectedBunny(void);
	~InfectedBunny(void);

	bool IsActive() const;

	void SetState(IBunnyState *bunnyState);
	const IBunnyState *GetState() const;

	void SetPosition(const sm::Vec3 &position);
	void SetMoveTarget(const sm::Vec3 &moveTarget);

	const sm::Vec3 GetPosition() const;
	const sm::Vec3 GetMoveTarget() const;

	void Update(float time, float seconds);
	void Draw(float time, float seconds, const sm::Matrix &viewMatrix);

	void Respawn(const sm::Vec3 &position);

	void Reset();

	float IsSpawning() const;
	void DecreaseSpawningProcess(float seconds);
	void SetHuntingTarget(HealthyBunny *healthyBunny);
	HealthyBunny *GetHuntingTarget();

	const sm::Vec3& GetTargetPosition() const;
	void SetTargetPosition(const sm::Vec3 &targetPosition);

	void RefreshNewTargetPosition(float seconds);

	Ticker& FuckingProgress();
	Ticker& RestingAfterFuckingProgress();

	bool& DidTellToGTFO();

	void ChangeFromInfected(HealthyBunny *hbunny);

	void MakeDamage(float damageValue);

	void Die();
	void KickOff(const sm::Vec3 &target);

	bool IsDying() const;

private:
	bool m_isActive;

	IBunnyState *m_bunnyState;

	ThrowTrajectory m_kickTrajectory;

	Model *m_bunnyModel;
	Animation *m_runAnim;
	Animation *m_walkAnim;
	Animation *m_fuckAnim;

	Model *m_dieHead;
	Model *m_dieBody;

	sm::Matrix m_dieBaseMatrix; // world matrix in the moment of die
	sm::Matrix m_dieBodyMatrix;
	sm::Matrix m_dieHeadMatrix;

	ThrowTrajectory m_dieBodyTrajectory;
	ThrowTrajectory m_dieHeadTrajectory;

	SparksGenerator *m_shotBloodParticles;
	SparksGenerator *m_dieBodyParticles;
	SparksGenerator *m_dieHeadParticles;

	sm::Vec3 m_dieBodyAxis;
	float m_dieBodyAngleProgress;
	float m_dieBodyAngleSpeed;
	sm::Vec3 m_dieHeadAxis;
	float m_dieHeadAngleProgress;
	float m_dieHeadAngleSpeed;

	float m_targetPositionRefreshColldown;

	float m_fuckProgressTime;
	int m_fuckMoveCycles;

	Ticker m_fuckingProgress;
	Ticker m_restingAfterFuckingProgress;

	bool m_didTellToGTFO;

	float m_spawningProgress;
	HealthyBunny *m_huntingTarget;

	float m_bleedingTime;
};

#endif

