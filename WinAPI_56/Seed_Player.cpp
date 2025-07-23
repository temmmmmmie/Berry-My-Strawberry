#include "pch.h"
#include "Seed_Player.h"

#include "KeyMgr.h"
#include "FlipbookPlayer.h"
#include "LevelMgr.h"
#include "Level.h"
#include "Level_Stage01.h"

#include "Player.h"
#include "HitBox.h"

void Seed_Player::ToIdle()
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

void Seed_Player::Enter()
{
	Player* OwnerActor = dynamic_cast<Player*>(GetOwnerActor());
	assert(OwnerActor);

	OwnerActor->SetState(PLAYER_STATE::SEED);
	HitBox* pbox = new HitBox(OwnerActor);
	pbox->SetPos(Vec2(500, 500));

	FlipbookPlayer* pFlipbookPlayer = OwnerActor->GetComponent<FlipbookPlayer>();
	pFlipbookPlayer->SetSpriteIdx(0);
	pFlipbookPlayer->SetCallback(bind(&Seed_Player::ToIdle, this));

	LevelMgr::GetInst()->GetCurrentLevel()->AddActor(PLAYER_PROJECTILE, pbox);
	DIR Direction = OwnerActor->GetDir();
	switch (Direction)
	{
	case DIR::UP:
		pFlipbookPlayer->Play(SEED_UP, 6.f, 0);
		break;
	case DIR::LEFT:
		pFlipbookPlayer->Play(SEED_LEFT, 6.f, 0);
		break;
	case DIR::DOWN:
		pFlipbookPlayer->Play(SEED_DOWN, 6.f, 0);
		break;
	case DIR::RIGHT:
		pFlipbookPlayer->Play(SEED_RIGHT, 6.f, 0);
		break;
	}

}

void Seed_Player::FinalTick()
{
}

void Seed_Player::Exit()
{
}

Seed_Player::Seed_Player()
{
}

Seed_Player::~Seed_Player()
{
}
