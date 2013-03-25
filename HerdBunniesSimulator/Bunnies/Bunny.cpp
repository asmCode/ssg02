#include "Bunny.h"

Bunny::Bunny(void)
{
}

Bunny::~Bunny(void)
{
}

void Bunny::UpdateMovement(float seconds, float movementSpeed)
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

float Bunny::GetHealth() const
{
	return m_health;
}

void Bunny::SetDestinationPosition(const sm::Vec3 &position)
{
	m_targetPosition = position;
}

