#include "pch.h"
#include "RigidBody.h"

#include "TimeMgr.h"


RigidBody::RigidBody()
	: Component(COMPONENT_TYPE::RIGIDBODY)
	, m_Mass(1.f)
	, m_FricCoef(1.f)
	, m_MaxSpeed(600.f)
	, m_Gravity(0.f)
	, m_MaxGravitySpeed(0.f)
	, m_Type(TOPVIEW)
	, m_JumpSpeed(0.f)
	, m_Ground(false)
	, m_AirMoveCoef(0.2f)
	, m_MaxJumpStack(1)
	, m_JumpStack(0)
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::Jump()
{
	if (m_MaxJumpStack <= m_JumpStack)
		return;

	m_GravityVelocity.y = -m_JumpSpeed;
	m_Ground = false;

	m_JumpStack += 1;
}

void RigidBody::FinalTick()
{
	if (m_Type == PLATFORMER)
	{
		Move_Platformer();
	}
	else if (m_Type == TOPVIEW)
	{
		Move_TopView();
	}

	// �� �ʱ�ȭ
	m_Force = Vec2(0.f, 0.f);
}

void RigidBody::Move_TopView()
{
	// ������ ���� ���� Ȯ��
	// ���� ���� ���ӵ� ���
	Vec2 vAccel = m_Force / m_Mass;

	// ���ӵ��� ���ؼ� �ӵ��� ��ȭ
	m_Velocity += vAccel * DT;

	// �����¿� ���ؼ� �ӵ��� ����
	Vec2 vFriction = -m_Velocity;
	vFriction.Normalize();
	vFriction *= m_FricCoef;

	if (m_Velocity.Length() < m_FricCoef * DT)
	{
		m_Velocity = Vec2(0.f, 0.f);
	}
	else
	{
		m_Velocity += vFriction * DT;
	}

	// �ִ�ӵ� ����
	if (m_MaxSpeed < m_Velocity.Length())
	{
		m_Velocity.Normalize();
		m_Velocity *= m_MaxSpeed;
	}

	// �ӵ��� ���� �̵�
	Vec2 vMove = m_Velocity * DT;
	Vec2 finalpos = GetOwner()->GetPos() + vMove;

	if (finalpos.x > 870)
		finalpos.x = 870;
	else if (finalpos.x < -870)
		finalpos.x = -870;

	if (finalpos.y > 400)
		finalpos.y = 400;
	else if (finalpos.y < -250)
		finalpos.y = -250;

	GetOwner()->SetPos(finalpos);
}

void RigidBody::Move_Platformer()
{
	// ������ ���� ���� Ȯ��
	// ���� ���� ���ӵ� ���
	Vec2 vAccel = m_Force / m_Mass;

	// ���ӵ��� ���ؼ� �ӵ��� ��ȭ

	// ���߿��� ������ ���� �ӵ� ��ȭ���� �� ����
	if (!m_Ground)
	{
		m_Velocity += vAccel * DT * m_AirMoveCoef;
	}
	else
	{
		m_Velocity += vAccel * DT;
	}

	// �����¿� ���ؼ� �ӵ��� ����
	Vec2 vFriction = Vec2(0.f, 0.f);
	if (m_Ground)
	{
		vFriction = -m_Velocity;
		vFriction.Normalize();
		vFriction *= m_FricCoef;
	}

	if (m_Velocity.Length() < m_FricCoef * DT)
	{
		m_Velocity = Vec2(0.f, 0.f);
	}
	else
	{
		m_Velocity += vFriction * DT;
	}

	// �ִ�ӵ� ����
	if (m_MaxSpeed < m_Velocity.Length())
	{
		m_Velocity.Normalize();
		m_Velocity *= m_MaxSpeed;
	}

	// �߷¿� ���� �ӵ� ���
	// ������ ���ִٸ�
	if (m_Ground)
	{
		m_GravityVelocity = Vec2(0.f, 0.f);
	}
	else
	{
		// �߷� ���ӵ��� ���� �ӵ� ����
		m_GravityVelocity.y += m_Gravity * DT;

		// �ִ� �߷¼ӵ� ����
		if (m_GravityVelocity.Length() > m_MaxGravitySpeed)
		{
			m_GravityVelocity.Normalize();
			m_GravityVelocity *= m_MaxGravitySpeed;
		}
	}

	Vec2 vFinalVelocity = m_Velocity + m_GravityVelocity;

	// �ӵ��� ���� �̵�
	Vec2 vMove = vFinalVelocity * DT;
	GetOwner()->SetPos(GetOwner()->GetPos() + vMove);
}
