#include "pch.h"
#include "Ground.h"

#include "Collider.h"

Ground::Ground()
	: m_Collider(nullptr)
{
	m_Collider = AddComponent(new Collider);
	m_Collider->SetScale(Vec2(700.f, 100.f));
}

Ground::~Ground()
{
}

void Ground::Tick()
{
}

void Ground::Render(HDC _dc)
{
}

void Ground::BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

void Ground::Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

void Ground::EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}