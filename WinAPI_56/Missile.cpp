#include "pch.h"
#include "Missile.h"


#include "LevelMgr.h"
#include "Level.h"

#include "TimeMgr.h"
#include "Collider.h"
#include "RigidBody.h"


Missile::Missile()
	: m_Collider(nullptr)
	, m_Speed(500.f)
	, m_Angle(90.f)
	, m_Target(nullptr)
	, m_TargetType(ACTOR_TYPE::ACTOR_END)
	, m_DetectRange(1000.f)
	, m_RotateSpeed(90.f)
	, m_Age(0.f)
	, m_Life(10.f)
	, m_Rigid(nullptr)
{
	SetScale(Vec2(20.f, 20.f));

	m_Collider = AddComponent(new Collider);
	m_Collider->SetScale(Vec2(20.f, 20.f));
	m_Collider->SetOffset(Vec2(0.f, 0.f));

	m_Rigid = AddComponent(new RigidBody);
	m_Rigid->SetMass(1.f);
	m_Rigid->SetMaxSpeed(500.f);
}

Missile::~Missile()
{
}

void Missile::Begin()
{
	int a = 10;
}

void Missile::Tick()
{
	// Move_Angle();

	//Move_DirVector();

	//Move_GuidedMissile();

	Move_RigidBody();

	m_Age += DT;
	if (m_Life < m_Age)
		Destroy();
}

void Missile::Render(HDC _dc)
{
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc
		, (int)(vPos.x - vScale.x / 2.f)
		, (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f)
		, (int)(vPos.y + vScale.y / 2.f));
}


void Missile::Move_Angle()
{
	Vec2 vPos = GetPos();

	float Radian = (m_Angle / 180.f) * PI;

	vPos.x += m_Speed * cosf(Radian) * DT;
	vPos.y -= m_Speed * sinf(Radian) * DT;

	SetPos(vPos);
}

void Missile::Move_DirVector()
{
	Vec2 vPos = GetPos();

	// Velocity �� �ʴ� �̵���
	// DT �� ���ؼ� �̹������ӿ� �̵��� �� �ະ �̵����� ����
	// ������ ���� �̹������� �̵����� Pos �� ������
	vPos += m_Velocity * DT;

	SetPos(vPos);	
}

void Missile::Move_GuidedMissile()
{
	// ���� ����� ã�´�.
	if (nullptr == m_Target)
	{
		FindTarget();
	}

	// Ÿ���� ã�� ��������, ���� �������� ����
	if (nullptr == m_Target)
	{
		Move_DirVector();
	}

	// Ÿ���� ������ Ÿ���� �����Ѵ�.
	else
	{
		// ���⺤�͸� �̿��ؼ� �����̱�
		Vec2 vPos = GetPos();
		Vec2 vTargetPos = m_Target->GetPos();

		// ���� ���� ���⺤��
		Vec2 vCurDir = m_Velocity;
		vCurDir.Normalize();

		// �̻����� Ÿ���� ���ϴ� ���⺤��
		Vec2 vTargetDir = vTargetPos - vPos;

		// ���� ���⺤�Ϳ� Ÿ���� ���ϴ� ���Ͱ� ���� ��ġ(����)�ϸ� ���̻� ȸ���� ���� �ʾƾ� ��
		vTargetDir.Normalize();
		float Dot = vCurDir.Dot(vTargetDir);
		float Theta = acos(Dot);

		// �������� �̳���, Ÿ���� ���ֺ������� ����
		if (Theta < 0.08f)
		{
			vCurDir = vTargetDir;
			vCurDir.Normalize();
		}
		else
		{
			// ������ ȸ�� ������ ã���־�� ��
			float RotateDir = vCurDir.Cross(vTargetDir);

			if (0 < RotateDir)
				RotateDir = -1.f;
			else
				RotateDir = 1.f;

			// ���⺤�͸� ȸ���ӵ��� �°� ȸ����
			vCurDir = Rotate(vCurDir, (m_RotateSpeed + m_Age * 9.f) * DT * RotateDir);
			vCurDir.Normalize();
		}

		DrawDebugLine(GetPos(), GetPos() + vCurDir * 50.f, PEN_TYPE::BLUE, 0.f);

		// ȸ���� �������� �ӵ��� ������
		vCurDir *= m_Velocity.Length();
		m_Velocity = vCurDir;

		// Velocity �������� �̵��Ѵ�.
		Move_DirVector();
	}

	DrawDebugCircle(GetPos(), m_DetectRange, PEN_TYPE::BLUE, 0.f);
}
void Missile::Move_RigidBody()
{
	// ���� ����� ã�´�.
	if (nullptr == m_Target)
	{
		FindTarget();
	}

	// Ÿ���� ����
	if (nullptr == m_Target)
		return;

	Vec2 vPos = GetPos();
	Vec2 vTargetPos = m_Target->GetPos();

	// �̻����� Ÿ���� ���� ����
	Vec2 vTargetDir = vTargetPos - vPos;
	vTargetDir.Normalize();
	vTargetDir *= 1000.f;

	m_Rigid->AddForce(vTargetDir);
}
void Missile::FindTarget()
{	
	// ���� ���׷쿡 ���� Actor �߿���, �̻��ϰ� ���� ����� ����� Ÿ������ ã�´�.
	// ���� ���׷��� �����Ǿ����� ������, Ÿ���� ã�� �ʴ´�.
	if (ACTOR_TYPE::ACTOR_END == m_TargetType)
		return;

	// ���� ������ �����ؼ�, ������� �׷쿡 ����(ACTOR_TYPE) ��� Actor ���� �����´�.
	Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
	const vector<Actor*>& vecActor = pCurLevel->GetActor(m_TargetType);

	// �̻����� ��ġ
	Vec2 vPos = GetPos();

	float fMinDist = m_DetectRange;

	for (size_t i = 0; i < vecActor.size(); ++i)
	{
		// Ÿ�� �ĺ��� ��ġ������ �Ÿ�
		float fDist = vPos.Distance(vecActor[i]->GetPos());

		if (fDist < fMinDist)
		{
			m_Target = vecActor[i];
			fMinDist = fDist;
		}
	}


}

void Missile::BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
	Destroy();
}

void Missile::Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

void Missile::EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}