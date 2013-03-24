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

static sm::Matrix CalcBoneMatrixZ(const sm::Vec3 &jointStart, const sm::Vec3 &jointEnd)
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

sm::Matrix Player::GetViewMatrix() const
{
	return (CalcBoneMatrixZ(m_position, m_position + m_lookTarget) *
		sm::Matrix::TranslateMatrix(0, GameProps::PlayerHeight, 0)).GetInversed();
}

