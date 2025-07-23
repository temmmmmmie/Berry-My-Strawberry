#include "pch.h"
#include "Collider.h"

#include "Actor.h"
#include "CollisionMgr.h"
#include "Camera.h"

Collider::Collider()
	: Component(COMPONENT_TYPE::COLLIDER)
	, m_OverlapCount(0)
	,m_Enabled(true)
{
	SetName(L"Collider");
}

Collider::~Collider()
{
}

void Collider::FinalTick()
{	
	if (m_Enabled) {
		m_FinalPos = GetOwner()->GetPos() + m_OffsetPos;
	
		ACTOR_TYPE Type = GetOwner()->GetActorType();

		CollisionMgr::GetInst()->RegisterCollider(this, Type);


		Vec2 vRenderPos = Camera::GetInst()->GetRenderPos(m_FinalPos);	

		if(0 == m_OverlapCount)
			DrawDebugRect(vRenderPos, m_Scale, PEN_TYPE::GREEN, 0.f);
		else if(0 < m_OverlapCount)
			DrawDebugRect(vRenderPos, m_Scale, PEN_TYPE::RED, 0.f);
	}
}

void Collider::BeginOverlap(Collider* _Other)
{
	++m_OverlapCount;

	GetOwner()->BeginOverlap(this, _Other->GetOwner(), _Other);
}

void Collider::Overlap(Collider* _Other)
{
	GetOwner()->Overlap(this, _Other->GetOwner(), _Other);
}

void Collider::EndOverlap(Collider* _Other)
{
	--m_OverlapCount;

	GetOwner()->EndOverlap(this, _Other->GetOwner(), _Other);
}
