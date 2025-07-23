#include "pch.h"
#include "Level.h"

#include "Actor.h"

Level::Level()
{
}

Level::~Level()
{
	for (UINT i = ACTOR_TYPE::DEFAULT; i < ACTOR_END; ++i)
	{
		for (size_t j = 0; j < m_vecActor[i].size(); ++j)
		{
			delete m_vecActor[i][j];
		}
	}
}

void Level::Begin()
{
	for (UINT i = ACTOR_TYPE::DEFAULT; i < ACTOR_END; ++i)
	{
		for (size_t j = 0; j < m_vecActor[i].size(); ++j)
		{
			m_vecActor[i][j]->Begin();
		}
	}
}

void Level::Tick()
{
	for (UINT i = ACTOR_TYPE::DEFAULT; i < ACTOR_END; ++i)
	{
		for (size_t j = 0; j < m_vecActor[i].size(); ++j)
		{
			m_vecActor[i][j]->Tick();
		}
	}
}

void Level::FinalTick()
{
	for (UINT i = ACTOR_TYPE::DEFAULT; i < ACTOR_END; ++i)
	{
		for (size_t j = 0; j < m_vecActor[i].size(); ++j)
		{
			m_vecActor[i][j]->FinalTick();
		}
	}
}

void Level::Render(HDC _dc)
{
	for (UINT i = ACTOR_TYPE::DEFAULT; i < ACTOR_END; ++i)
	{
		vector<Actor*>::iterator iter = m_vecActor[i].begin();
		for (; iter != m_vecActor[i].end(); )
		{
			if ((*iter)->IsDead())
			{
				iter = m_vecActor[i].erase(iter);
			}
			else
			{
				(*iter)->Render(_dc);
				++iter;
			}
		}
	}
}


void Level::AddActor(ACTOR_TYPE _Idx, Actor* _Actor)
{
	m_vecActor[_Idx].push_back(_Actor);

	_Actor->m_ActorType = _Idx;
}

void Level::ClearActor(ACTOR_TYPE _Type)
{
	for (size_t i = 0; i < m_vecActor[(UINT)_Type].size(); ++i)
	{
		m_vecActor[(UINT)_Type][i]->Destroy();
	}

	m_vecActor[(UINT)_Type].clear();
}

void Level::ClearAllActor()
{
	for (UINT i = 0; i < ACTOR_TYPE::ACTOR_END; ++i)
	{
		ClearActor((ACTOR_TYPE)i);
	}
}
