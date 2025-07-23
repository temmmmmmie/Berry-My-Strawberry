#include "pch.h"
#include "Wagon.h"

#include "AssetMgr.h"
#include "RenderMgr.h"
#include "GameMgr.h"

#include "ATexture.h"
#include "Collider.h"
#include "FlipbookPlayer.h"

void Wagon::StoreStrawberry()
{
	GameMgr::GetInst()->AddStrawberry();
	m_FlipbookPlayer->SetSpriteIdx(0);
	m_FlipbookPlayer->Play(0, 2, 1);

}

void Wagon::Begin()
{
}

void Wagon::Tick()
{
}

void Wagon::Render(HDC _dc)
{
	m_FlipbookPlayer->Render(_dc);
}

void Wagon::BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

void Wagon::Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

void Wagon::EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

Wagon::Wagon()
	:m_FlipbookPlayer(nullptr)
{
	m_Collider = AddComponent(new Collider);
	m_FlipbookPlayer = AddComponent(new FlipbookPlayer);

	m_FlipbookPlayer->AddFlipbook(0, AssetMgr::GetInst()->FindFlipbook(L"WAGON"));
	m_FlipbookPlayer->Play(0, 2, 1);

	m_Collider->SetOffset(Vec2(50, 0));
	m_Collider->SetScale(Vec2(200, 140.f));
}

Wagon::~Wagon()
{
}
