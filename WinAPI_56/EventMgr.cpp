#include "pch.h"
#include "EventMgr.h"

#include "LevelMgr.h"
#include "Level.h"
#include "Actor.h"


EventMgr::EventMgr()
{

}

EventMgr::~EventMgr()
{

}

void EventMgr::Tick()
{
	// Dead ������Ʈ ����
	ClearGarbage();

	// �̺�Ʈ ó��
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		switch (m_vecEvent[i].Type)
		{
		case EVENT::CREATE_ACTOR:
		{
			Actor* pActor = (Actor*)m_vecEvent[i].Data0;
			ACTOR_TYPE Type = (ACTOR_TYPE)m_vecEvent[i].Data1;

			Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
			pCurLevel->AddActor(Type, pActor);
		}
			break;
		case EVENT::DESTROY_ACTOR:
		{
			Actor* pActor = (Actor*)m_vecEvent[i].Data0;

			// ���� �������°� �ƴѰ�쿡�� ó��
			// ���� ���͸� �ߺ����� ������ ����ó���ϴ°��� �����ϱ� ����
			if (!pActor->IsDead())
			{
				// Actor �� �����������·� �����.
				pActor->m_Dead = true;

				// Dead ���°� �� Actor �� �������뿡 ����־�д�.
				m_Garbage.push_back(pActor);
			}
		}
			break;
		case EVENT::CHANGE_LEVEL:
			LEVEL_TYPE NextLevel = (LEVEL_TYPE)m_vecEvent[i].Data0;

			LevelMgr::GetInst()->ChangeLevel(NextLevel);
			break;
		}
	}

	m_vecEvent.clear();
}


void EventMgr::ClearGarbage()
{
	for (size_t i = 0; i < m_Garbage.size(); ++i)
	{
		delete m_Garbage[i];
	}

	m_Garbage.clear();
}