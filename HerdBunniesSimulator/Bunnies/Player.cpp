#include "Player.h"
#include "GameProps.h"
#include "InterfaceProvider.h"
#include "DrawingRoutines.h"
#include "../BunniesView/IShapesRenderer.h"
#include <Graphics/Model.h>
#include <Graphics/Animation.h>
#include <Graphics/Content/Content.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <stdio.h>
#include <assert.h>

Player::Player() :
	m_position(0, 0, 0),
	m_lookTarget(0, 0, -1),
	m_forwardMove(0.0f),
	m_strafeMove(0.0f),
	m_kickProgress(0.0f),
	m_isKicking(false),
	m_kickCooldown(0.0f)
{
	m_leg = InterfaceProvider::GetContent()->Get<Model>("leg");
	assert(m_leg != NULL);

	m_kickAnim = InterfaceProvider::GetContent()->Get<Animation>("leg");
	assert(m_kickAnim != NULL);
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

	float playerWidth = 2.0f;

	if (m_position.x > 50.0f - playerWidth)
		m_position.x = 50.0f - playerWidth;

	if (m_position.x < -50.0f + playerWidth)
		m_position.x = -50.0f + playerWidth;

	if (m_position.z > 50.0f - playerWidth)
		m_position.z = 50.0f - playerWidth;
	
	if (m_position.z < -50.0f + playerWidth)
		m_position.z = -50.0f + playerWidth;

	if (m_isKicking)
	{
		m_kickAnim->Update(m_kickProgress, sm::Matrix::IdentityMatrix(), seconds);
		m_kickProgress += seconds;

		if (m_kickProgress > m_kickAnim->GetAnimLength())
		{
			m_isKicking = false;
		}
	}

	m_kickCooldown += seconds;
}

void Player::Draw(float time, float seconds)
{
	if (m_isKicking)
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		DrawingRoutines::DrawCelShaded(m_leg, sm::Matrix::IdentityMatrix(), sm::Matrix::TranslateMatrix(-8.87f, -12, -22));
	}
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

sm::Vec3 Player::GetEyePosition() const
{
	return sm::Vec3(m_position.x, GameProps::PlayerHeight, m_position.z);
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
	return (sm::Matrix::TranslateMatrix(0, GameProps::PlayerHeight, 0) *
		CalcBoneMatrixZ(m_position, m_position + m_lookTarget)).GetInversed();
}

void Player::Kick()
{
	if (m_isKicking)
		return;

	m_kickProgress = 0.0f;
	m_isKicking = true;
	m_kickCooldown = 0.0f;
}

bool Player::IsKicking() const
{
	return m_isKicking;
}

bool Player::IsAbleToKick() const
{
	return m_kickCooldown >= GameProps::KickCooldown;
}
