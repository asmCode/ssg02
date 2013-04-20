#include "Bunny.h"

#include <Graphics/Animation.h>

Bunny::Bunny(void)
{
	m_walkAnimLength = 0;
	m_walkAnimProgress = 0.0f;
	m_delayBetweenJumps = 0.1f;
	m_jumpDistance = 1.0f;
	m_delayTime = 0.0f;
}

Bunny::~Bunny(void)
{
}

void Bunny::UpdateMovement(float seconds, float movementSpeed)
{
	if (GetWalkAnimation() == NULL)
		return;

	if (m_walkAnimLength == 0.0f)
		m_walkAnimLength = GetWalkAnimation()->GetAnimLength();

	bool canMove = false;

	if (m_walkAnimProgress < m_walkAnimLength)
	{
		//canMove = true;

		m_walkAnimProgress += seconds;
	}
	else if (m_delayTime < m_delayBetweenJumps)
	{
		m_delayTime += seconds;
	}
	else if (m_delayTime >= m_delayBetweenJumps)
	{
		m_delayTime = 0.0f;
		m_walkAnimProgress = 0.0f;
	}

	if (m_walkAnimProgress < m_walkAnimLength * 0.85f)
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
		m_position += m_moveTarget * m_jumpDistance * movementSpeed * seconds;
	}
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
	GetWalkAnimation()->Update(m_walkAnimProgress, sm::Matrix::IdentityMatrix(), seconds);
}
