#include "pch.h"
#include "Player.h"

#include "LevelMgr.h"
#include "Level.h"
#include "PathMgr.h"
#include "TimeMgr.h"
#include "AssetMgr.h"
#include "KeyMgr.h"
#include "RenderMgr.h"
#include "EventMgr.h"
#include "Camera.h"

#include "ATexture.h"
#include "ASprite.h"

#include "Collider.h"
#include "FlipbookPlayer.h"
#include "AFlipbook.h"
#include "RigidBody.h"

#include "StateMachine.h"
#include "Idle_Player.h"
#include "Move_Player.h"
#include "Attack_Player.h"
#include "Seed_Player.h"
#include "Potion_Player.h"
#include "Water_Player.h"
#include "Interact_Player.h"

#include "Missile.h"
void LoadAnimation(FlipbookPlayer* _FlipbookPlayer);
Player::Player()
	: m_Image(nullptr)
	, m_Sprite(nullptr)
	, m_Collider(nullptr)
	, m_FlipbookPlayer(nullptr)
	, m_Dir(DIR::DOWN)
	, m_AttackRange(100)
	, m_hand(ITEMS::NONE)
{
	// Player 가 컴포넌트를 가진다.
	m_Collider = AddComponent(new Collider);
	m_FlipbookPlayer = AddComponent(new FlipbookPlayer);
	m_StateMachine = AddComponent(new StateMachine);

	LoadAnimation(m_FlipbookPlayer);

	m_FlipbookPlayer->Play(IDLE_LEFT, 10.f, 0);
	
	// StateMacine 에 상태추가
	m_StateMachine->AddState(L"Idle", new Idle_Player);
	m_StateMachine->AddState(L"Move", new Move_Player);
	m_StateMachine->AddState(L"Attack", new Attack_Player);
	m_StateMachine->AddState(L"Potion", new Potion_Player);
	m_StateMachine->AddState(L"Seed", new Seed_Player);
	m_StateMachine->AddState(L"Water", new Water_Player);
	m_StateMachine->AddState(L"Interact", new Interact_Player);
	m_StateMachine->ChangeState(L"Idle");

	// 충돌체 설정
	m_Collider->SetOffset(Vec2(0, 0));
	m_Collider->SetScale(Vec2(80.f, 120.f));

	// 강체 컴포넌트 추가
	m_Rigid = AddComponent(new RigidBody);
	m_Rigid->SetType(RIGIDBODY_TYPE::TOPVIEW);

	m_Rigid->SetMass(0.5f);
	m_Rigid->SetFricCoef(1500.f);
	m_Rigid->SetGravity(980.f);
	m_Rigid->SetMaxGravitySpeed(2000.f);
	m_Rigid->SetJumpSpeed(600.f);
	m_Rigid->SetMaxJumpStack(0);
}

Player::~Player()
{

}

void Player::Tick()
{	

}

void Player::Render(HDC _dc)
{
	// FlipbookPlayer 컴포넌트가 Player 의 렌더링을 담당
	m_FlipbookPlayer->Render(_dc);
}

void Player::BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{

}

void Player::Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
	if(_OtherCollider->m_Istrigger == false)SetPos(GetPos() - _OwnCollider->GetPenetratedVec() * 0.02f);
}

void Player::EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{

}

void LoadAnimation(FlipbookPlayer* _FlipbookPlayer)
{
	// FlipbookPlayer 컴포넌트에, AssetMgr 에서 찾아온 Flipbook 을 재생목록으로 집어넣는다.	
	_FlipbookPlayer->AddFlipbook(IDLE_DOWN, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_IDLEDOWN"));
	_FlipbookPlayer->AddFlipbook(IDLE_LEFT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_IDLELEFT"));
	_FlipbookPlayer->AddFlipbook(IDLE_UP, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_IDLEUP"));
	_FlipbookPlayer->AddFlipbook(IDLE_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_IDLERIGHT"));

	_FlipbookPlayer->AddFlipbook(NONE_MOVE_DOWN, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_WALK_DOWN"));
	_FlipbookPlayer->AddFlipbook(NONE_MOVE_LEFT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_WALK_LEFT"));
	_FlipbookPlayer->AddFlipbook(NONE_MOVE_UP, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_UP"));
	_FlipbookPlayer->AddFlipbook(NONE_MOVE_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_WALK_RIGHT"));

	_FlipbookPlayer->AddFlipbook(BERRY_DOWN, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_BERRYDOWN"));
	_FlipbookPlayer->AddFlipbook(BERRY_LEFT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_BERRYLEFT"));
	_FlipbookPlayer->AddFlipbook(BERRY_UP, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_IDLEUP"));
	_FlipbookPlayer->AddFlipbook(BERRY_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_BERRYRIGHT"));

	_FlipbookPlayer->AddFlipbook(BERRY_MOVE_DOWN, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_BERRY_WALK_DOWN"));
	_FlipbookPlayer->AddFlipbook(BERRY_MOVE_LEFT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_BERRY_WALK_LEFT"));
	_FlipbookPlayer->AddFlipbook(BERRY_MOVE_UP, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_UP"));
	_FlipbookPlayer->AddFlipbook(BERRY_MOVE_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_BERRY_WALK_RIGHT"));

	_FlipbookPlayer->AddFlipbook(POTION_DOWN, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_POTIONDOWN"));
	_FlipbookPlayer->AddFlipbook(POTION_LEFT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_POTIONLEFT"));
	_FlipbookPlayer->AddFlipbook(POTION_UP, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_IDLEUP"));
	_FlipbookPlayer->AddFlipbook(POTION_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_POTIONRIGHT"));

	_FlipbookPlayer->AddFlipbook(POTION_MOVE_DOWN, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_POTION_WALK_DOWN"));
	_FlipbookPlayer->AddFlipbook(POTION_MOVE_LEFT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_POTION_WALK_LEFT"));
	_FlipbookPlayer->AddFlipbook(POTION_MOVE_UP, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_UP"));
	_FlipbookPlayer->AddFlipbook(POTION_MOVE_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_POTION_WALK_RIGHT"));

	_FlipbookPlayer->AddFlipbook(SEED_DOWN, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_SEEDDOWN"));
	_FlipbookPlayer->AddFlipbook(SEED_LEFT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_SEEDLEFT"));
	_FlipbookPlayer->AddFlipbook(SEED_UP, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_IDLEUP"));
	_FlipbookPlayer->AddFlipbook(SEED_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_SEEDRIGHT"));

	_FlipbookPlayer->AddFlipbook(SEED_MOVE_DOWN, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_SEED_WALK_DOWN"));
	_FlipbookPlayer->AddFlipbook(SEED_MOVE_LEFT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_SEED_WALK_LEFT"));
	_FlipbookPlayer->AddFlipbook(SEED_MOVE_UP, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_UP"));
	_FlipbookPlayer->AddFlipbook(SEED_MOVE_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_SEED_WALK_RIGHT"));

	_FlipbookPlayer->AddFlipbook(SWORD_DOWN, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_SWORDDOWN"));
	_FlipbookPlayer->AddFlipbook(SWORD_LEFT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_SWORDLEFT"));
	_FlipbookPlayer->AddFlipbook(SWORD_UP, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_SWORDUP"));
	_FlipbookPlayer->AddFlipbook(SWORD_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_SWORDRIGHT"));

	_FlipbookPlayer->AddFlipbook(SWORD_MOVE_DOWN, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_SWORD_WALK_DOWN"));
	_FlipbookPlayer->AddFlipbook(SWORD_MOVE_LEFT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_SWORD_WALK_LEFT"));
	_FlipbookPlayer->AddFlipbook(SWORD_MOVE_UP, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_SWORD_WALK_UP"));
	_FlipbookPlayer->AddFlipbook(SWORD_MOVE_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_SWORD_WALK_RIGHT"));

	_FlipbookPlayer->AddFlipbook(WATER_DOWN, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_WATERDOWN"));
	_FlipbookPlayer->AddFlipbook(WATER_LEFT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_WATERLEFT"));
	_FlipbookPlayer->AddFlipbook(WATER_UP, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_IDLEUP"));
	_FlipbookPlayer->AddFlipbook(WATER_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_WATERRIGHT"));

	_FlipbookPlayer->AddFlipbook(WATER_MOVE_DOWN, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_WATER_WALK_DOWN"));
	_FlipbookPlayer->AddFlipbook(WATER_MOVE_LEFT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_WATER_WALK_LEFT"));
	_FlipbookPlayer->AddFlipbook(WATER_MOVE_UP, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_UP"));
	_FlipbookPlayer->AddFlipbook(WATER_MOVE_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_WATER_WALK_RIGHT"));

	_FlipbookPlayer->AddFlipbook(ATTACK_DOWN, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_ATTACK_DOWN"));
	_FlipbookPlayer->AddFlipbook(ATTACK_LEFT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_ATTACK_LEFT"));
	_FlipbookPlayer->AddFlipbook(ATTACK_UP, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_ATTACK_UP"));
	_FlipbookPlayer->AddFlipbook(ATTACK_RIGHT, AssetMgr::GetInst()->FindFlipbook(L"ALBENTIO_ATTACK_RIGHT"));
}