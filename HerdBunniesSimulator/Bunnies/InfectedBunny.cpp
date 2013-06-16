#include "InfectedBunny.h"
#include "IBunnyState.h"
#include "HealthyBunny.h"
#include "Respawning.h"
#include "InterfaceProvider.h"
#include "Dying.h"
#include "RestingAfterFucking.h"
#include "Flying.h"
#include "GameProps.h"
#include "DrawingRoutines.h"

#include <Graphics/Content/Content.h>
#include <Utils/Randomizer.h>

#include <stddef.h>
#include <assert.h>

InfectedBunny::InfectedBunny() :
	m_isActive(false),
	m_spawningProgress(0.0f),
	m_huntingTarget(NULL),
	m_bunnyState(NULL),
	m_targetPositionRefreshColldown(0.0f),
	m_fuckingProgress(GameProps::FuckingTime)
{
	m_bunnyModel = InterfaceProvider::GetContent()->Get<Model>("ibunny");
	m_runAnim = InterfaceProvider::GetContent()->Get<Animation>("ibunny_run");
	m_walkAnim = InterfaceProvider::GetContent()->Get<Animation>("ibunny_walk");
	m_fuckAnim = InterfaceProvider::GetContent()->Get<Animation>("ibunny_fuck");
	m_dieHead = InterfaceProvider::GetContent()->Get<Model>("ibunny_die_head");
	m_dieBody = InterfaceProvider::GetContent()->Get<Model>("ibunny_die_body");

	assert(m_bunnyModel != NULL);
	assert(m_runAnim != NULL);
	assert(m_walkAnim != NULL);
	assert(m_fuckAnim != NULL);
	assert(m_dieHead != NULL);
	assert(m_dieBody != NULL);

	InitFuckAnimBounds(m_bunnyModel);

	m_currentModel = m_bunnyModel;
}

InfectedBunny::~InfectedBunny(void)
{
}

bool InfectedBunny::IsActive() const
{
	return m_isActive;
}

void InfectedBunny::SetState(IBunnyState *bunnyState)
{
	assert(bunnyState != NULL);

	if (m_bunnyState != NULL)
		m_bunnyState->Leave(this);
	m_bunnyState = bunnyState;
	m_bunnyState->Enter(this);
}

const IBunnyState *InfectedBunny::GetState() const
{
	assert(m_bunnyState != NULL);

	return m_bunnyState;
}

void InfectedBunny::SetPosition(const sm::Vec3 &position)
{
	m_position = position;
}

void InfectedBunny::SetMoveTarget(const sm::Vec3 &moveTarget)
{
	m_moveTarget = moveTarget;
}

const sm::Vec3 InfectedBunny::GetPosition() const
{
	return m_position;
}

const sm::Vec3 InfectedBunny::GetMoveTarget() const
{
	return m_moveTarget;
}

void InfectedBunny::Update(float time, float seconds)
{
	assert(m_bunnyState != NULL);

	m_bunnyState->Update(this, time, seconds);
}

static sm::Matrix CalcBoneMatrixZ(const sm::Vec3 &jointStart, const sm::Vec3 &jointEnd) // todo 
{
	sm::Matrix rot = sm::Matrix::IdentityMatrix();

	sm::Vec3 zAxis = (jointEnd - jointStart).GetNormalized().GetReversed();
	sm::Vec3 xAxis = (zAxis * sm::Vec3(0, 1, 0)).GetNormalized();
	sm::Vec3 yAxis = xAxis * zAxis;

	rot.a[0] = xAxis.x;
	rot.a[1] = xAxis.y;
	rot.a[2] = xAxis.z;

	rot.a[4] = yAxis.x;
	rot.a[5] = yAxis.y;
	rot.a[6] = yAxis.z;

	rot.a[8] = zAxis.x;
	rot.a[9] = zAxis.y;
	rot.a[10] = zAxis.z;

	return sm::Matrix::TranslateMatrix(jointStart) * rot;
}

void InfectedBunny::Draw(float time, float seconds, const sm::Matrix &viewMatrix)
{
	if (m_bunnyState->GetStateType() != IBunnyState::State_Dying)
	{
		this->Bunny::Draw(time, seconds);

		DrawingRoutines::DrawCelShaded(
			m_bunnyModel,
			viewMatrix,
			CalcBoneMatrixZ(m_position, m_position + m_moveTarget) * sm::Matrix::RotateAxisMatrix(3.1415f, 0, 1, 0));
	}
	else
	{
		DrawingRoutines::DrawCelShaded(
			m_dieBody,
			viewMatrix,
			m_dieBodyMatrix);

		DrawingRoutines::DrawCelShaded(
			m_dieHead,
			viewMatrix,
			m_dieHeadMatrix);
	}
}

void InfectedBunny::Respawn(const sm::Vec3 &position)
{
	m_isActive = true;
	m_spawningProgress = GameProps::SpawningTime;
	m_health = 100.0f;
	SetPosition(position);
	SetState(Respawning::GetInstance());
}

void InfectedBunny::Reset()
{
	m_moveTarget = sm::Vec3(0, 0, -1);
	m_isActive = false;	
	m_huntingTarget = NULL;
	m_health = 100.0f;
	m_targetPositionRefreshColldown = 0.0f;
}

float InfectedBunny::IsSpawning() const
{
	return m_spawningProgress > 0.0f;
}

void InfectedBunny::DecreaseSpawningProcess(float seconds)
{
	m_spawningProgress -= seconds;
	if (m_spawningProgress < 0.0f)
		m_spawningProgress = 0.0f;
}

void InfectedBunny::SetHuntingTarget(HealthyBunny *healthyBunny)
{
	m_huntingTarget = healthyBunny;
}

HealthyBunny *InfectedBunny::GetHuntingTarget()
{
	return m_huntingTarget;
}

const sm::Vec3& InfectedBunny::GetTargetPosition() const
{
	return m_targetPosition;
}

void InfectedBunny::SetTargetPosition(const sm::Vec3 &targetPosition)
{
	m_targetPosition = targetPosition;
}

void InfectedBunny::RefreshNewTargetPosition(float seconds)
{
	static Randomizer random;

	float distance = (m_targetPosition - m_position).GetLength();

	m_targetPositionRefreshColldown -= seconds;
	if (m_targetPositionRefreshColldown <= 0.0f || distance <= 0.4f)
	{
		m_targetPositionRefreshColldown = random.GetFloat(
			GameProps::RefreshNewTargetPositionFrom,
			GameProps::RefreshNewTargetPositionTo);

		sm::Vec3 newPos(random.GetFloat(-50.0f, 50.0f), 0.0f, random.GetFloat(-50.0f, 50.0f));
		SetDestinationPosition(newPos);
	}
}

Ticker& InfectedBunny::FuckingProgress()
{
	return m_fuckingProgress;
}

Ticker& InfectedBunny::RestingAfterFuckingProgress()
{
	return m_restingAfterFuckingProgress;
}

bool& InfectedBunny::DidTellToGTFO()
{
	return m_didTellToGTFO;
}

void InfectedBunny::ChangeFromInfected(HealthyBunny *hbunny)
{
	assert(hbunny != NULL);

	m_isActive = true;
	m_health = 100.0f;
	SetPosition(hbunny->GetPosition());
	SetMoveTarget(hbunny->GetMoveTarget());
	m_restingAfterFuckingProgress.SetTicker(GameProps::RestingAfterChangedToInfectedTime);
	SetState(RestingAfterFucking::GetInstance());
}

void InfectedBunny::MakeDamage(float damageValue)
{
	m_health -= damageValue;
	if (m_health < 0.0f)
		m_health = 0.0f;

	if (m_health == 0.0f)
	{
		Die();
	}
}

void InfectedBunny::Die()
{
	if (GetState()->GetStateType() == IBunnyState::State_Fucking ||
		GetState()->GetStateType() == IBunnyState::State_Hunting)
		m_huntingTarget->SetToIdle();

	SetState(Dying::GetInstance());
}

void InfectedBunny::KickOff(const sm::Vec3 &target)
{
	if (GetState()->GetStateType() == IBunnyState::State_Fucking ||
		GetState()->GetStateType() == IBunnyState::State_Hunting)
		m_huntingTarget->SetToIdle();

	//m_flyingVector = target;

	m_kickTrajectory.Throw(m_position, target, 25.0f, 30.0f);

	SetState(Flying::GetInstance());
}

