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
	// Dead 오브젝트 삭제
	ClearGarbage();

	// 이벤트 처리
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

			// 삭제 예정상태가 아닌경우에만 처리
			// 동일 액터를 중복으로 여러번 삭제처리하는것을 방지하기 위함
			if (!pActor->IsDead())
			{
				// Actor 를 삭제예정상태로 만든다.
				pActor->m_Dead = true;

				// Dead 상태가 된 Actor 를 쓰레기통에 집어넣어둔다.
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