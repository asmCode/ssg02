#include "Bunny.h"

#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/Animation.h>

#include "d:\stuff\Infected Bunnies\code\ssg02\HerdBunniesSimulator\Framework\Graphics\Property.h"

Bunny::Bunny(void)
{
	m_moveAnimProgress = 0.0f;
	m_delayTime = 0.0f;

	m_currentAnim = NULL;
	m_currentModel = NULL;
}

Bunny::~Bunny(void)
{
}

void Bunny::UpdateMovement(float seconds, float movementSpeed, float delayBetweenJumps)
{
	if (m_currentAnim == NULL)
		return;

	float animLength = m_currentAnim->GetAnimLength();

	bool canMove = false;

	if (m_moveAnimProgress < animLength)
	{
		m_moveAnimProgress += seconds;
	}
	else if (m_delayTime < delayBetweenJumps)
	{
		m_delayTime += seconds;
	}
	else if (m_delayTime >= delayBetweenJumps)
	{
		m_delayTime = 0.0f;
		m_moveAnimProgress = 0.0f;
	}

	if (m_moveAnimProgress < animLength * 0.85f)
		canMove = true;

	if (canMove)
	{
		sm::Vec3 moveDirection = m_targetPosition - m_position;
		if (moveDirection.GetLength() <= 0.1f) // TODO
		{
			m_position = m_targetPosition;
			return;
		}
	
		m_moveTarget = moveDirection.GetNormalized();
		m_position += m_moveTarget * movementSpeed * seconds;
	}

	m_currentAnimTime = m_moveAnimProgress;
}

float Bunny::GetHealth() const
{
	return m_health;
}

void Bunny::SetDestinationPosition(const sm::Vec3 &position)
{
	m_targetPosition = position;
}

void Bunny::Draw(float time, float seconds)
{
	if (m_currentAnim != NULL)
		m_currentAnim->Update(m_currentAnimTime, sm::Matrix::IdentityMatrix(), seconds);
}

void Bunny::InitFuckAnimBounds(Model *model)
{
	Mesh *bodyMesh = model->FindMesh("body");
	assert(bodyMesh  != NULL);

	Property *fuckAnimBounds = bodyMesh->FindProperty("fuck_anim_bounds");
	assert(fuckAnimBounds != NULL);

	int valDummy;
	bool stopKeyDumy;
	fuckAnimBounds->GetKeyframe(0, m_fuckAnimStart, valDummy, stopKeyDumy);
	fuckAnimBounds->GetKeyframe(1, m_fuckAnimEnd, valDummy, stopKeyDumy);
}

