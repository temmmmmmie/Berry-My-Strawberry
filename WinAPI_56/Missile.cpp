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

	// Velocity 는 초당 이동량
	// DT 를 곱해서 이번프레임에 이동할 각 축별 이동량을 구함
	// 위에서 구한 이번프레임 이동량을 Pos 에 더해줌
	vPos += m_Velocity * DT;

	SetPos(vPos);	
}

void Missile::Move_GuidedMissile()
{
	// 추적 대상을 찾는다.
	if (nullptr == m_Target)
	{
		FindTarget();
	}

	// 타겟을 찾지 못했으면, 가던 방향으로 간다
	if (nullptr == m_Target)
	{
		Move_DirVector();
	}

	// 타겟이 있으면 타겟을 추적한다.
	else
	{
		// 방향벡터를 이용해서 움직이기
		Vec2 vPos = GetPos();
		Vec2 vTargetPos = m_Target->GetPos();

		// 현재 진행 방향벡터
		Vec2 vCurDir = m_Velocity;
		vCurDir.Normalize();

		// 미사일이 타겟을 향하는 방향벡터
		Vec2 vTargetDir = vTargetPos - vPos;

		// 현재 방향벡터와 타겟을 향하는 벡터가 거의 일치(동일)하면 더이상 회전을 하지 않아야 함
		vTargetDir.Normalize();
		float Dot = vCurDir.Dot(vTargetDir);
		float Theta = acos(Dot);

		// 오차범위 이내면, 타겟을 마주본것으로 간주
		if (Theta < 0.08f)
		{
			vCurDir = vTargetDir;
			vCurDir.Normalize();
		}
		else
		{
			// 적절한 회전 방향을 찾아주어야 함
			float RotateDir = vCurDir.Cross(vTargetDir);

			if (0 < RotateDir)
				RotateDir = -1.f;
			else
				RotateDir = 1.f;

			// 방향벡터를 회전속도에 맞게 회전함
			vCurDir = Rotate(vCurDir, (m_RotateSpeed + m_Age * 9.f) * DT * RotateDir);
			vCurDir.Normalize();
		}

		DrawDebugLine(GetPos(), GetPos() + vCurDir * 50.f, PEN_TYPE::BLUE, 0.f);

		// 회전한 방향으로 속도를 설정함
		vCurDir *= m_Velocity.Length();
		m_Velocity = vCurDir;

		// Velocity 방향으로 이동한다.
		Move_DirVector();
	}

	DrawDebugCircle(GetPos(), m_DetectRange, PEN_TYPE::BLUE, 0.f);
}
void Missile::Move_RigidBody()
{
	// 추적 대상을 찾는다.
	if (nullptr == m_Target)
	{
		FindTarget();
	}

	// 타겟이 없다
	if (nullptr == m_Target)
		return;

	Vec2 vPos = GetPos();
	Vec2 vTargetPos = m_Target->GetPos();

	// 미사일이 타겟을 향한 방향
	Vec2 vTargetDir = vTargetPos - vPos;
	vTargetDir.Normalize();
	vTargetDir *= 1000.f;

	m_Rigid->AddForce(vTargetDir);
}
void Missile::FindTarget()
{	
	// 추적 대상그룹에 속한 Actor 중에서, 미사일과 가장 가까운 대상을 타겟으로 찾는다.
	// 추적 대상그룹이 지정되어있지 않으면, 타겟을 찾지 않는다.
	if (ACTOR_TYPE::ACTOR_END == m_TargetType)
		return;

	// 현재 레벨에 접근해서, 추적대상 그룹에 속한(ACTOR_TYPE) 모든 Actor 들을 가져온다.
	Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
	const vector<Actor*>& vecActor = pCurLevel->GetActor(m_TargetType);

	// 미사일의 위치
	Vec2 vPos = GetPos();

	float fMinDist = m_DetectRange;

	for (size_t i = 0; i < vecActor.size(); ++i)
	{
		// 타겟 후보의 위치까지의 거리
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