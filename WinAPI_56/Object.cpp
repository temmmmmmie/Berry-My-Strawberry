#include "pch.h"
#include "Object.h"

#include "AssetMgr.h"
#include "RenderMgr.h"

#include "Animator.h"
#include "ATexture.h"
#include "Collider.h"

void Object::Begin()
{
}

void Object::Tick()
{
}

void Object::Render(HDC _dc)
{
	Vec2 vPos = GetRenderPos();
	Vec2 Scale = GetScale();
	RenderMgr::GetInst()->Draw(m_Texture, vPos.x, vPos.y, m_Texture->GetWidth() * Scale.x, m_Texture->GetHeight() * Scale.y);
}

void Object::BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

void Object::Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

void Object::EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
}

Object::Object(ATexture* _tex, bool _hascollider, Vec2 _scale, Vec2 _offset, AnimationStruct* _animation)
	:m_Texture(_tex),
	m_HasCollider(_hascollider)
{
	if (m_HasCollider) {
		m_Collider = AddComponent(new Collider);
		m_Collider->SetOffset(_offset);
		m_Collider->SetScale(_scale);
	}
	m_Animator = AddComponent(new Animator);

	if(_animation)m_Animator->AddAnimation(*_animation);
}

Object::~Object()
{
}
