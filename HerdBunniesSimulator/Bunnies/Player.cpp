#include "Player.h"
#include "GameProps.h"
#include "InterfaceProvider.h"
#include "../BunniesView/IShapesRenderer.h"
#include <stdio.h>
#include <assert.h>

Player::Player() :
	m_position(0, 0, 0),
	m_lookTarget(0, 0, -1),
	m_forwardMove(0.0f),
	m_strafeMove(0.0f)
{
}

Player::~Player(void)
{
}

void Player::Update(float time, float seconds)
{
	sm::Vec3 moveTarget(m_lookTarget.x, 0, m_lookTarget.z);
	moveTarget.Normalize();
	sm::Vec3 strafeTarget(-moveTarget.z, 0.0f, moveTarget.x);

	moveTarget *= -m_forwardMove * GameProps::FarmerMoveSpeed;
	strafeTarget *= m_strafeMove * GameProps::FarmerMoveSpeed;

	m_position += (moveTarget + strafeTarget) * seconds;
}

void Player::Draw(float time, float seconds)
{
	IShapesRenderer *shapesRenderer = InterfaceProvider::GetShapesRenderer();

	shapesRenderer->DrawPlayer(this);
}

void Player::SetLookTarget(const sm::Vec3 &lookTarget)
{
	m_lookTarget = lookTarget;
}

void Player::SetForwardMove(float forwardMove)
{
	assert(forwardMove >= -1.0f && forwardMove <= 1.0f);

	m_forwardMove = forwardMove;
}

void Player::SetStrafeMove(float strafeMove)
{
	assert(strafeMove >= -1.0f && strafeMove <= 1.0f);

	m_strafeMove = strafeMove;
}

const sm::Vec3& Player::GetPosition() const
{
	return m_position;
}

const sm::Vec3& Player::GetLookTarget() const
{
	return m_lookTarget;
}

