#include "pch.h"
#include "Tool.h"

#include "AssetMgr.h"
#include "RenderMgr.h"

#include "ATexture.h"
#include "Collider.h"

void Tool::Begin()
{
}

void Tool::Tick()
{
}

void Tool::Render(HDC _dc)
{
	if (m_Enbled) {
		Vec2 vPos = GetRenderPos();
		Vec2 Scale = GetScale();
		RenderMgr::GetInst()->Draw(m_Texture, vPos.x, vPos.y, m_Texture->GetWidth() * Scale.x, m_Texture->GetHeight() * Scale.y);
	}
}

void Tool::BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

void Tool::Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

void Tool::EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

Tool::Tool(tooltype type)
	:m_Texture(nullptr),
	m_Tooltype(type),
	m_Enbled(true)
{
	m_Collider = AddComponent(new Collider);
	switch (m_Tooltype)
	{
	case tooltype::SWORD:
		m_Texture = AssetMgr::GetInst()->LoadTexture(L"itemSword", L"Texture\\itemSword.png");
		break;
	case tooltype::WATER:
		m_Texture = AssetMgr::GetInst()->LoadTexture(L"itemWateringcan", L"Texture\\itemWateringcan.png");
		break;
	case tooltype::POTION:
		m_Texture = AssetMgr::GetInst()->LoadTexture(L"itemPossion", L"Texture\\itemPossion.png");
		break;
	case tooltype::SEED:
		m_Texture = AssetMgr::GetInst()->LoadTexture(L"itemSeed", L"Texture\\itemSeed.png");
		break;
	}

	m_Collider->m_Istrigger = true;
	m_Collider->SetOffset(Vec2(0, 0));
	m_Collider->SetScale(Vec2(70.f, 70.f));
}

Tool::~Tool()
{
}
