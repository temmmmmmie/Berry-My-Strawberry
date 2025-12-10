#include "pch.h"
#include "Move_Player.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "LevelMgr.h"

#include "FlipbookPlayer.h"
#include "RigidBody.h"
#include "Level_Stage01.h"

#include "HitBox.h"

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

		Player* OwnerActor = dynamic_cast<Player*>(GetOwnerActor());
		assert(OwnerActor);

		OwnerActor->SetState(PLAYER_STATE::INTERACT);

		DIR Direction = OwnerActor->GetDir();
		HitBox* pbox = new HitBox(OwnerActor);
		pbox->SetPos(Vec2(500, 500));

		FlipbookPlayer* pFlipbookPlayer = OwnerActor->GetComponent<FlipbookPlayer>();
		pFlipbookPlayer->SetSpriteIdx(0);
		pFlipbookPlayer->SetCallback(bind(&Move_Player::ToIdle, this));

		LevelMgr::GetInst()->GetCurrentLevel()->AddActor(PLAYER_PROJECTILE, pbox);

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

void Move_Player::ToIdle()
{
	Player* OwnerActor = dynamic_cast<Player*>(GetOwnerActor());
	assert(OwnerActor);

	OwnerActor->SetState(PLAYER_STATE::IDLE);

	DIR Direction = OwnerActor->GetDir();

	FlipbookPlayer* pFlipbookPlayer = OwnerActor->GetComponent<FlipbookPlayer>();
	pFlipbookPlayer->SetSpriteIdx(0);

	Level* pLevel = LevelMgr::GetInst()->m_CurLevel;
	Level_Stage01* pCurLevel = dynamic_cast<Level_Stage01*>(pLevel);
	pCurLevel->ClearActor(PLAYER_PROJECTILE);

	switch (Direction)
	{
	case DIR::UP:
		pFlipbookPlayer->Play(IDLE_UP, 6.f, 0);
		break;
	case DIR::LEFT:
		pFlipbookPlayer->Play(IDLE_LEFT, 6.f, 0);
		break;
	case DIR::DOWN:
		pFlipbookPlayer->Play(IDLE_DOWN, 6.f, 0);
		break;
	case DIR::RIGHT:
		pFlipbookPlayer->Play(IDLE_RIGHT, 6.f, 0);
		break;
	}
	GetOwner()->ChangeState(L"Idle");
	pFlipbookPlayer->DeleteCallback();
}
