#include "pch.h"
#include "Rabbit.h"

#include "TimeMgr.h"
#include "PathMgr.h"
#include "AssetMgr.h"
#include "RenderMgr.h"
#include "LevelMgr.h"
#include "Level.h"
#include "FlipbookPlayer.h"
#include "StateMachine.h"
#include "RigidBody.h"

#include "Collider.h"
#include "ATexture.h"
#include "Strawberrry.h"

#include "Idle_Rabbit.h"
#include "Trace_Rabbit.h"
#include "Attack_Rabbit.h"
#include "Die_Rabbit.h"

Rabbit::Rabbit()
	: m_Collider(nullptr)
	, m_FlipbookPlayer(nullptr)
	, m_Dir(DIR::LEFT)
	, m_MoveRange(50)

{
	m_Collider = AddComponent(new Collider);
	m_FlipbookPlayer = AddComponent(new FlipbookPlayer);
	m_StateMachine = AddComponent(new StateMachine);

	m_Collider->SetOffset(Vec2(0.f, 25.f));
	m_Collider->SetScale(Vec2(100.f, 100.f));

	m_FlipbookPlayer->AddFlipbook((int)RABBIT_ANIM::IDLE_LEFT, AssetMgr::GetInst()->FindFlipbook(L"RABBIT_IDLELEFT"));
	m_FlipbookPlayer->AddFlipbook((int)RABBIT_ANIM::IDLE_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"RABBIT_IDLERIGHT"));

	m_FlipbookPlayer->AddFlipbook((int)RABBIT_ANIM::MOVE_LEFT, AssetMgr::GetInst()->FindFlipbook(L"RABBIT_MOVELEFT"));
	m_FlipbookPlayer->AddFlipbook((int)RABBIT_ANIM::MOVE_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"RABBIT_MOVERIGHT"));

	m_FlipbookPlayer->AddFlipbook((int)RABBIT_ANIM::DIE_LEFT, AssetMgr::GetInst()->FindFlipbook(L"RABBIT_DIELEFT"));
	m_FlipbookPlayer->AddFlipbook((int)RABBIT_ANIM::DIE_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"RABBIT_DIERIGHT"));

	m_FlipbookPlayer->AddFlipbook((int)RABBIT_ANIM::ATTACK, AssetMgr::GetInst()->FindFlipbook(L"RABBIT_ATTACK"));

	m_FlipbookPlayer->Play((int)RABBIT_ANIM::IDLE_LEFT, 10.f, 0);

	m_StateMachine->AddState(L"Idle", new Idle_Rabbit);
	m_StateMachine->AddState(L"Trace", new Trace_Rabbit);
	m_StateMachine->AddState(L"Attack", new Attack_Rabbit);
	m_StateMachine->AddState(L"Die", new Die_Rabbit);
	m_StateMachine->ChangeState(L"Idle");

	m_Rigid = AddComponent(new RigidBody);
	m_Rigid->SetType(RIGIDBODY_TYPE::TOPVIEW);
	m_Rigid->SetMaxSpeed(100);
	m_Rigid->SetMass(0.5f);
	m_Rigid->SetFricCoef(1800.f);
	m_Rigid->SetGravity(980.f);
	m_Rigid->SetMaxGravitySpeed(2000.f);
	m_Rigid->SetJumpSpeed(600.f);
	m_Rigid->SetMaxJumpStack(0);
}

Rabbit::~Rabbit()
{	
}

void Rabbit::Settarget()
{
	Vec2 pos = GetRandomPos(GetPos(), m_MoveRange);

	pos.x = Clamp(pos.x, -700.f, 700.f);
	pos.y = Clamp(pos.y, -150.f, 300.f);
	
	m_Target = pos;
}

void Rabbit::Move(Vec2 _target)
{
	Vec2 vPos = GetPos();
	Vec2 vTargetPos = _target;

	// 미사일이 타겟을 향한 방향
	Vec2 vTargetDir = vTargetPos - vPos;
	vTargetDir.Normalize();
	vTargetDir *= 1000.f;

	m_Rigid->AddForce(vTargetDir);

}

void Rabbit::Begin()
{

}

void Rabbit::Tick()
{
	if ( abs(GetPos().x - m_Target.x) < 10 && abs(GetPos().y - m_Target.y) < 10) Arrived = true;
	else Arrived = false;

	if (m_Rigid->GetVelocity().x > 0) {
		m_Dir = DIR::RIGHT;
	}
	else {
		m_Dir = DIR::LEFT;
	}

	if (GetPos().y > 130) {
		LevelMgr::GetInst()->GetCurrentLevel()->MoveActor(this, ENERMY2);
	}
	else
	{
		LevelMgr::GetInst()->GetCurrentLevel()->MoveActor(this, ENERMY);
	}
}

void Rabbit::Render(HDC _dc)
{
	m_FlipbookPlayer->Render(_dc);
}

void Rabbit::BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{

}

void Rabbit::Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{

}

void Rabbit::EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{

}

void Rabbit::Die()
{
	if (nullptr == dynamic_cast<Die_Rabbit*>(m_StateMachine->GetCurState())) {
		m_StateMachine->ChangeState(L"Die");
	}
}
