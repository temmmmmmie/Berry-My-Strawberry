#include "pch.h"
#include "Idle_Player.h"

#include "KeyMgr.h"
#include "AssetMgr.h"
#include "ASound.h"

#include "Player.h"
#include "FlipbookPlayer.h"

Idle_Player::Idle_Player()
{
}

Idle_Player::~Idle_Player()
{
}

void Idle_Player::Enter()
{
	Player* OwnerActor = dynamic_cast<Player*>(GetOwnerActor());
	assert(OwnerActor);

	OwnerActor->SetState(PLAYER_STATE::IDLE);

	DIR Direction = OwnerActor->GetDir();

	FlipbookPlayer* pFlipbookPlayer = OwnerActor->GetComponent<FlipbookPlayer>();
	pFlipbookPlayer->SetSpriteIdx(0);
	switch (OwnerActor->GetHand())
	{
	case ITEMS::NONE:
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
		break;
	case ITEMS::STRAWBERRY:
		switch (Direction)
		{
		case DIR::UP:
			pFlipbookPlayer->Play(BERRY_UP, 6.f, 0);
			break;
		case DIR::LEFT:
			pFlipbookPlayer->Play(BERRY_LEFT, 6.f, 0);
			break;
		case DIR::DOWN:
			pFlipbookPlayer->Play(BERRY_DOWN, 6.f, 0);
			break;
		case DIR::RIGHT:
			pFlipbookPlayer->Play(BERRY_RIGHT, 6.f, 0);
			break;
		}
		break;
	case ITEMS::POTION:
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
		break;
	case ITEMS::SEED:
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
		break;
	case ITEMS::SWORD:
		switch (Direction)
		{
		case DIR::UP:
			pFlipbookPlayer->Play(SWORD_UP, 6.f, 0);
			break;
		case DIR::LEFT:
			pFlipbookPlayer->Play(SWORD_LEFT, 6.f, 0);
			break;
		case DIR::DOWN:
			pFlipbookPlayer->Play(SWORD_DOWN, 6.f, 0);
			break;
		case DIR::RIGHT:
			pFlipbookPlayer->Play(SWORD_RIGHT, 6.f, 0);
			break;
		}
		break;
	case ITEMS::WATER:
		switch (Direction)
		{
		case DIR::UP:
			pFlipbookPlayer->Play(WATER_UP, 6.f, 0);
			break;
		case DIR::LEFT:
			pFlipbookPlayer->Play(WATER_LEFT, 6.f, 0);
			break;
		case DIR::DOWN:
			pFlipbookPlayer->Play(WATER_DOWN, 6.f, 0);
			break;
		case DIR::RIGHT:
			pFlipbookPlayer->Play(WATER_RIGHT, 6.f, 0);
			break;
		}
		break;
	}

}

void Idle_Player::FinalTick()
{
	Player* OwnerActor = dynamic_cast<Player*>(GetOwnerActor());
	assert(OwnerActor);

	if (KEY_PRESSED(W))
	{
		OwnerActor->SetDir(DIR::UP);
		GetOwner()->ChangeState(L"Move");
	}	
	else if (KEY_PRESSED(A))
	{
		OwnerActor->SetDir(DIR::LEFT);
		GetOwner()->ChangeState(L"Move");
	}
	else if (KEY_PRESSED(S))
	{
		OwnerActor->SetDir(DIR::DOWN);
		GetOwner()->ChangeState(L"Move");
	}	
	else if (KEY_PRESSED(D))
	{
		OwnerActor->SetDir(DIR::RIGHT);
		GetOwner()->ChangeState(L"Move");
	}

	if (KEY_TAP(SPACE))
	{
		ITEMS item = OwnerActor->GetHand();
		switch (item)
		{
		case ITEMS::NONE:
			GetOwner()->ChangeState(L"Interact");
			break;
		case ITEMS::STRAWBERRY:
			GetOwner()->ChangeState(L"Interact");
			break;
		case ITEMS::SWORD:
			AssetMgr::GetInst()->FindSound(L"Sword")->Play();
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

void Idle_Player::Exit()
{

}