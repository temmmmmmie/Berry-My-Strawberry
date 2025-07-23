#include "pch.h"
#include "Potion_Player.h"

#include "KeyMgr.h"
#include "FlipbookPlayer.h"
#include "LevelMgr.h"
#include "Level.h"
#include "Level_Stage01.h"

#include "Player.h"
#include "HitBox.h"

void Potion_Player::ToIdle()
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

void Potion_Player::Enter()
{
	Player* OwnerActor = dynamic_cast<Player*>(GetOwnerActor());
	assert(OwnerActor);

	OwnerActor->SetState(PLAYER_STATE::POTION);
	HitBox* pbox = new HitBox(OwnerActor);
	pbox->SetPos(Vec2(500, 500));

	FlipbookPlayer* pFlipbookPlayer = OwnerActor->GetComponent<FlipbookPlayer>();
	pFlipbookPlayer->SetSpriteIdx(0);
	pFlipbookPlayer->SetCallback(bind(&Potion_Player::ToIdle, this));

	LevelMgr::GetInst()->GetCurrentLevel()->AddActor(PLAYER_PROJECTILE, pbox);

	DIR Direction = OwnerActor->GetDir();
	switch (Direction)
	{
	case DIR::UP:
		pFlipbookPlayer->Play(POTION_UP, 6.f, 0);
		break;
	case DIR::LEFT:
		pFlipbookPlayer->Play(POTION_LEFT, 6.f, 0);
		break;
	case DIR::DOWN:
		pFlipbookPlayer->Play(POTION_DOWN, 6.f, 0);
		break;
	case DIR::RIGHT:
		pFlipbookPlayer->Play(POTION_RIGHT, 6.f, 0);
		break;
	}
}

void Potion_Player::FinalTick()
{
}

void Potion_Player::Exit()
{
}

Potion_Player::Potion_Player()
{
}

Potion_Player::~Potion_Player()
{
}
