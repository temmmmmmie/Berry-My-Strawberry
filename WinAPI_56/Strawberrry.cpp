#include "pch.h"
#include "Strawberrry.h"

#include "AssetMgr.h"
#include "RenderMgr.h"
#include "GameMgr.h"
#include "TimeMgr.h"

#include "ASound.h"
#include "ATexture.h"
#include "Collider.h"
#include "FlipbookPlayer.h"

void Strawberrry::Begin()
{
}

void Strawberrry::Tick()
{
	
}

void Strawberrry::Render(HDC _dc)
{
	m_FlipbookPlayer->Render(_dc);
}

void Strawberrry::BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

void Strawberrry::Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
	if (_OtherActor->GetName() == L"Rabbit" && m_CurState > 1)
	{
		if (m_Eatentime > 2) Eaten();
		m_Eatentime += DT;
	}
}

void Strawberrry::EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
	if (_OtherActor->GetName() == L"Rabbit")
	{
		m_Eatentime = 0;
	}
}

void Strawberrry::Growth(int _growth)
{
	for (size_t i = 0; i < _growth; i++)
	{
		DelayedTask task
		{
			i * 0.5f,
			0.0f,
			[this, _growth]() { this->Growth(); }
		};
		GameMgr::GetInst()->AddDelay(task);
	}
}

void Strawberrry::Seed()
{
	if (m_CurState == 0) {
		m_CurState = 1;
		m_FlipbookPlayer->Play(1, 5, 0);
	}
}

void Strawberrry::Pick()
{
	m_FlipbookPlayer->SetCallback(bind(&Strawberrry::ToStage0, this));
	m_FlipbookPlayer->Play(7, 7, 1);
	m_CurState = 7;
}


void Strawberrry::Break()
{
	m_FlipbookPlayer->SetCallback(bind(&Strawberrry::ToStage0, this));
	m_FlipbookPlayer->Play(8, 7, 1);
	m_CurState = 7;
}

void Strawberrry::Eaten()
{
	AssetMgr::GetInst()->FindSound(L"StrawberryBreak")->Play();
	m_Eatentime = 0;
	m_FlipbookPlayer->SetCallback(bind(&Strawberrry::ToStage0, this));
	m_FlipbookPlayer->Play(9, 7, 1);
	m_CurState = 7;
}

void Strawberrry::ToStage0()
{
	m_CurState = 0;
	m_FlipbookPlayer->Play(0, 5, 0);
	m_FlipbookPlayer->DeleteCallback();
}


void Strawberrry::Growth()
{
	if (m_CurState < 6 && m_CurState > 0) {
		++m_CurState;
		m_FlipbookPlayer->Play(m_CurState, 5, 0);
	}
}


Strawberrry::Strawberrry()
	:m_CurTexture(nullptr),
	m_FlipbookPlayer(nullptr),
	m_CurState(0),
	m_Eatentime(0)
{
	m_Collider = AddComponent(new Collider);
	m_FlipbookPlayer = AddComponent(new FlipbookPlayer);
	
	m_FlipbookPlayer->AddFlipbook(1, AssetMgr::GetInst()->LoadFlipbook(L"STRAWBERRY0", L"Flipbook\\STRAWBERRY0.flip"));
	m_FlipbookPlayer->AddFlipbook(2, AssetMgr::GetInst()->LoadFlipbook(L"STRAWBERRY1", L"Flipbook\\STRAWBERRY1.flip"));
	m_FlipbookPlayer->AddFlipbook(3, AssetMgr::GetInst()->LoadFlipbook(L"STRAWBERRY2", L"Flipbook\\STRAWBERRY2.flip"));
	m_FlipbookPlayer->AddFlipbook(4, AssetMgr::GetInst()->LoadFlipbook(L"STRAWBERRY3", L"Flipbook\\STRAWBERRY3.flip"));
	m_FlipbookPlayer->AddFlipbook(5, AssetMgr::GetInst()->LoadFlipbook(L"STRAWBERRY4", L"Flipbook\\STRAWBERRY4.flip"));
	m_FlipbookPlayer->AddFlipbook(6, AssetMgr::GetInst()->LoadFlipbook(L"STRAWBERRY5", L"Flipbook\\STRAWBERRY5.flip"));
	m_FlipbookPlayer->AddFlipbook(7, AssetMgr::GetInst()->LoadFlipbook(L"STRAWBERRY_PICK", L"Flipbook\\STRAWBERRY_PICK.flip"));
	m_FlipbookPlayer->AddFlipbook(8, AssetMgr::GetInst()->LoadFlipbook(L"STRAWBERRY_BROKEN", L"Flipbook\\STRAWBERRY_BROKEN.flip"));
	m_FlipbookPlayer->AddFlipbook(9, AssetMgr::GetInst()->LoadFlipbook(L"STRAWBERRY_EATEN", L"Flipbook\\STRAWBERRY_EATEN.flip"));

	m_Collider->SetOffset(Vec2(0, 0));
	m_Collider->SetScale(Vec2(60.f, 40.f));
	m_Collider->m_Istrigger =true;
}

Strawberrry::~Strawberrry()
{
}
