#include "pch.h"
#include "Actor.h"

#include "Engine.h"
#include "Component.h"
#include "Camera.h"
#include "EventMgr.h"



Actor::Actor()
	: m_Pos{}
	, m_Scale{}
	, m_ActorType((ACTOR_TYPE)-1)
{
}

Actor::~Actor()
{
	for (size_t i = 0; i < m_vecCom.size(); ++i)
	{
		delete m_vecCom[i];
	}
}

void Actor::FinalTick()
{
	for (size_t i = 0; i < m_vecCom.size(); ++i)
	{
		m_vecCom[i]->FinalTick();
	}
}

void Actor::Render(HDC _dc)
{		
	HPEN hPrevPen = (HPEN)SelectObject(_dc, Engine::GetInst()->GetPen(PEN_TYPE::RED));
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_dc, Engine::GetInst()->GetBrush(BRUSH_TYPE::MAGENTA));

	Rectangle(_dc, m_Pos.x - m_Scale.x / 2, m_Pos.y - m_Scale.y / 2,
			       m_Pos.x + m_Scale.x / 2, m_Pos.y + m_Scale.y / 2);

	// DC �� ���� ������ ���� ����
	SelectObject(_dc, hPrevPen);
	SelectObject(_dc, hPrevBrush);
}


Component* Actor::GetComponent(const wstring& _Name)
{
	// �Էµ� �̸��̶� ������ �̸��� ���� ������Ʈ�� ã�Ƽ� ��ȯ
	for (size_t i = 0; i < m_vecCom.size(); ++i)
	{
		if (_Name == m_vecCom[i]->GetName())
			return m_vecCom[i];
	}

	return nullptr;
}

Component* Actor::GetComponent(COMPONENT_TYPE _Type)
{
	// �Էµ� Ÿ���̶� ������ Ÿ���� ���� ������Ʈ�� ã�Ƽ� ��ȯ
	for (size_t i = 0; i < m_vecCom.size(); ++i)
	{
		if (_Type == m_vecCom[i]->GetType())
			return m_vecCom[i];
	}

	return nullptr;
}

Vec2 Actor::GetRenderPos()
{
	return Camera::GetInst()->GetRenderPos(m_Pos);
}

void Actor::Destroy()
{
	tEventInfo info = {};

	info.Type = EVENT::DESTROY_ACTOR;
	info.Data0 = (DWORD_PTR)this;

	EventMgr::GetInst()->AddEvent(info);
}