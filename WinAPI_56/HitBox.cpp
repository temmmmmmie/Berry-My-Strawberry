#include "pch.h"
#include "HitBox.h"
#include "Player.h"

#include "Tool.h"
#include "Strawberrry.h"
#include "Rabbit.h"
#include "Wagon.h"
#include "Collider.h"
#include "ASound.h"
#include "RenderMgr.h"
#include "GameMgr.h"
#include "AssetMgr.h"
#include "Level_Stage01.h"

void HitBox::Begin()
{
	SetName(L"Hitbox");
}

void HitBox::Tick()
{
	DIR direction = m_Player->GetDir();
	Vec2 pos = m_Player->GetPos();
	int range = m_Player->GetAttackRange();
	switch (direction)
	{
	case DIR::DOWN:
		SetPos(pos + Vec2(0, range));
		break;
	case DIR::LEFT:
		SetPos(pos + Vec2(-range, 0));
		break;
	case DIR::UP:
		SetPos(pos + Vec2(0, -range));
		break;
	case DIR::RIGHT:
		SetPos(pos + Vec2(range, 0));
		break;
	}
	
}

void HitBox::Render(HDC _dc)
{
}

void HitBox::BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
	wstring	name = _OtherActor->GetName();
	if (_OtherActor->GetActorType() == INTERACTABLE) {
		if (name == L"Seed") {
			AssetMgr::GetInst()->FindSound(L"Grabbag")->Play();
			m_Player->SetHand(ITEMS::SEED);
		}
		else if (name == L"Water") {
			AssetMgr::GetInst()->FindSound(L"Grabbag")->Play();
			m_Player->SetHand(ITEMS::WATER);
		}
		else if (name == L"Sword") {
			AssetMgr::GetInst()->FindSound(L"Grabbag")->Play();
			m_Player->SetHand(ITEMS::SWORD);
		}
		else if (name == L"Potion") {
			AssetMgr::GetInst()->FindSound(L"Grabbag")->Play();
			m_Player->SetHand(ITEMS::POTION);
		}
		Tool* tool = dynamic_cast<Tool*>(_OtherActor);
		if (tool) {
			tool->Disable();
			GameMgr::GetInst()->Resetool(m_Player->GetHand());
			return;
		}

		if (name == L"Wagon"&& m_Player->GetHand() == ITEMS::STRAWBERRY) {
			m_Player->SetHand(ITEMS::NONE);

			DelayedTask task = {
				0.25f,
				0.0f,
				[this]() { this->CrowCall(); }
			};
			GameMgr::GetInst()->AddDelay(task);
			dynamic_cast<Wagon*>(_OtherActor)->StoreStrawberry();
			return;
		}


	}
	else if (_OtherActor->GetActorType() == STRAWBERRY) {
		Strawberrry* berry = dynamic_cast<Strawberrry*>(_OtherActor);
		if (berry) {
			switch (m_Player->GetHand())
			{
			case ITEMS::SWORD:
				if (berry->GetState() > 5) {
					berry->Break();
					AssetMgr::GetInst()->FindSound(L"StrawberryBreak")->Play();
				}
				break;
			case ITEMS::NONE:
				if (berry->GetState() == 6) {
					berry->Pick();
					m_Player->SetHand(ITEMS::STRAWBERRY);
					AssetMgr::GetInst()->FindSound(L"HarvestSound")->Play();
					GameMgr::GetInst()->Resetool();
				}
				break;
			case ITEMS::SEED:
				if (berry->GetState() == 6) {
					berry->Pick();
					m_Player->SetHand(ITEMS::STRAWBERRY);
					AssetMgr::GetInst()->FindSound(L"HarvestSound")->Play();
					GameMgr::GetInst()->Resetool();
				}
				else {
					AssetMgr::GetInst()->FindSound(L"Seed")->Play();
					berry->Seed();
				}
				break;
			case ITEMS::WATER:
				if (berry->GetState() == 6) {
					berry->Pick();
					m_Player->SetHand(ITEMS::STRAWBERRY);
					AssetMgr::GetInst()->FindSound(L"HarvestSound")->Play();
					GameMgr::GetInst()->Resetool();
				}
				else {
					AssetMgr::GetInst()->FindSound(L"Water")->Play();
					berry->Growth();
				}
				break;
			case ITEMS::POTION:
				if (berry->GetState() == 6) {
					berry->Pick();
					m_Player->SetHand(ITEMS::STRAWBERRY);
					AssetMgr::GetInst()->FindSound(L"HarvestSound")->Play();
					GameMgr::GetInst()->Resetool();
				}
				else {
					GameMgr::GetInst()->GetStageLevel()->SpawnRabbit(2);
					AssetMgr::GetInst()->FindSound(L"Water")->Play();
					berry->Growth(2);
				}
				break;
			}

		}
	}
	else if (m_Player->GetHand() == ITEMS::SWORD &&_OtherActor->GetActorType() == ENERMY) {
		dynamic_cast<Rabbit*>(_OtherActor)->Die();
	}
}

void HitBox::Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

void HitBox::EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

void HitBox::CrowCall()
{
	AssetMgr::GetInst()->FindSound(L"CrowSound")->Play();
}

HitBox::HitBox(Player* _owner)
	:m_Player(_owner)
{
	m_Collider = AddComponent(new Collider);
	m_Collider->SetOffset(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(100.f, 200.f));
}

HitBox::~HitBox()
{
}
