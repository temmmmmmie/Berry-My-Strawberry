#include "pch.h"
#include "Move_Player.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "Player.h"

#include "FlipbookPlayer.h"
#include "RigidBody.h"

Move_Player::Move_Player()
{
}

Move_Player::~Move_Player()
{
}

void Move_Player::Enter()
{
	Player* OwnerActor = dynamic_cast<Player*>(GetOwnerActor());
	assert(OwnerActor);

	OwnerActor->SetState(PLAYER_STATE::MOVE);

	ChangeFlipbook();

	OwnerActor->GetRigidBody()->SetMaxSpeed(400.f);
}

void Move_Player::FinalTick()
{
	// 키 입력에 따른 이동
	Move();

	// 플립북 재생 관리
	CheckAnim();
	
}

void Move_Player::Exit()
{
}




void Move_Player::Move()
{
	Player* OwnerActor = dynamic_cast<Player*>(GetOwnerActor());
	assert(OwnerActor);

	if (KEY_PRESSED(W))
		OwnerActor->GetRigidBody()->AddForce(Vec2(0.f, -1500.f));
	if (KEY_PRESSED(S))
		OwnerActor->GetRigidBody()->AddForce(Vec2(0.f, 1500.f));

	if (KEY_PRESSED(A))
		OwnerActor->GetRigidBody()->AddForce(Vec2(-1500.f, 0.f));
	if (KEY_PRESSED(D))
		OwnerActor->GetRigidBody()->AddForce(Vec2(1500.f, 0.f));
}

void Move_Player::CheckAnim()
{
	Player* OwnerActor = dynamic_cast<Player*>(GetOwnerActor());
	assert(OwnerActor);

	// 위를 누르고있는데, 현재 방향이 위가 아니라면
	if (KEY_TAP(W) && DIR::UP != OwnerActor->GetDir())
	{
		OwnerActor->SetDir(DIR::UP);
		ChangeFlipbook();
	}
		
	else if (KEY_TAP(A) && DIR::LEFT != OwnerActor->GetDir())
	{
		OwnerActor->SetDir(DIR::LEFT);
		ChangeFlipbook();
	}

	else if (KEY_TAP(S) && DIR::DOWN != OwnerActor->GetDir())
	{
		OwnerActor->SetDir(DIR::DOWN);
		ChangeFlipbook();
	}

	else if (KEY_TAP(D) && DIR::RIGHT != OwnerActor->GetDir())
	{
		OwnerActor->SetDir(DIR::RIGHT);
		ChangeFlipbook();
	}

	// 키 입력을 뗀 경우
	if (KEY_RELEASED(W))
	{
		OwnerActor->SetDir(DIR::UP);
		GetOwner()->ChangeState(L"Idle");
	}
	if (KEY_RELEASED(A))
	{
		OwnerActor->SetDir(DIR::LEFT);
		GetOwner()->ChangeState(L"Idle");
	}
	if (KEY_RELEASED(S))
	{
		OwnerActor->SetDir(DIR::DOWN);
		GetOwner()->ChangeState(L"Idle");
	}
	if (KEY_RELEASED(D))
	{
		OwnerActor->SetDir(DIR::RIGHT);
		GetOwner()->ChangeState(L"Idle");
	}

	if (KEY_TAP(SPACE))
	{
		ITEMS item = OwnerActor->GetHand();
		switch (item)
		{
		case ITEMS::NONE:
			GetOwner()->ChangeState(L"Interact");
			break;
		case ITEMS::SWORD:
			GetOwner()->ChangeState(L"Attack");
			break;
		case ITEMS::WATER:
			GetOwner()->ChangeState(L"Water");
			break;
		case ITEMS::POTION:
			GetOwner()->ChangeState(L"Potion");
			break;
		case ITEMS::SEED:
			GetOwner()->ChangeState(L"Seed");
			break;
		}
	}


}

void Move_Player::ChangeFlipbook()
{
	Player* OwnerActor = dynamic_cast<Player*>(GetOwnerActor());
	assert(OwnerActor);

	DIR Direction = OwnerActor->GetDir();
	PLAYER_STATE State = OwnerActor->GetState();

	FlipbookPlayer* pFlipbookPlayer = OwnerActor->GetComponent<FlipbookPlayer>();
	pFlipbookPlayer->Play((((UINT)OwnerActor->GetHand()) + 6) * 4 + (int)Direction, 15.f, 0);
}
