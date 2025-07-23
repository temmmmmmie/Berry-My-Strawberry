#include "pch.h"
#include "CollisionMgr.h"

#include "Actor.h"
#include "Collider.h"

CollisionMgr::CollisionMgr()
	: m_Matrix{}
{

}

CollisionMgr::~CollisionMgr()
{

}

void CollisionMgr::Tick()
{
	for (UINT Row = 0; Row < ACTOR_END; ++Row)
	{
		for (UINT Col = Row; Col < ACTOR_END; ++Col)
		{
			if (m_Matrix[Row] & (1 << Col))
			{
				CollisionActor((ACTOR_TYPE)Row, (ACTOR_TYPE)Col);
			}
		}
	}

	// 등록되어있던 충돌체들을 전부 해제시킨다.
	for (UINT i = 0; i < ACTOR_END; ++i)
	{
		m_vecCollider[i].clear();
	}
}

void CollisionMgr::CollisionActor(ACTOR_TYPE _Row, ACTOR_TYPE _Col)
{
	for (size_t i = 0; i < m_vecCollider[_Row].size(); ++i)
	{
		for (size_t j = 0; j < m_vecCollider[_Col].size(); ++j)
		{
			COLLIDER_ID ColID = {};
			ColID.Left = m_vecCollider[_Row][i]->GetID();
			ColID.Right = m_vecCollider[_Col][j]->GetID();			
			
			// ColID.ID == 두 충돌체로만 만들어 낼 수 있는 고유한 8바이트 정수
			map<DWORD_PTR, bool>::iterator iter = m_ColInfo.find(ColID.ID);

			if (iter == m_ColInfo.end())
			{
				m_ColInfo.insert(make_pair(ColID.ID, false));
				iter = m_ColInfo.find(ColID.ID);
			}		
			
			bool IsDead = m_vecCollider[_Row][i]->GetOwner()->IsDead()
				          || m_vecCollider[_Col][j]->GetOwner()->IsDead();			

			// 두 충돌체가 현재 겹쳐있다
			if (IsOverlap(m_vecCollider[_Row][i], m_vecCollider[_Col][j]))
			{
				// 이전에도 겹쳐있었다.
				if (iter->second)
				{
					if (IsDead)
					{
						m_vecCollider[_Row][i]->EndOverlap(m_vecCollider[_Col][j]);
						m_vecCollider[_Row][i]->SetPenetratedVec(Vec2(0, 0));
						m_vecCollider[_Col][j]->EndOverlap(m_vecCollider[_Row][i]);
						m_vecCollider[_Col][j]->SetPenetratedVec(Vec2(0, 0));
					}

					else
					{
						m_vecCollider[_Row][i]->Overlap(m_vecCollider[_Col][j]);
						m_vecCollider[_Col][j]->Overlap(m_vecCollider[_Row][i]);
					}					
				}

				// 이전에는 떨어져 있었다.
				else
				{
					if (!IsDead)
					{
						m_vecCollider[_Row][i]->BeginOverlap(m_vecCollider[_Col][j]);
						m_vecCollider[_Col][j]->BeginOverlap(m_vecCollider[_Row][i]);
					}					
				}	

				iter->second = true;
			}

			// 현재 겹쳐있지 않다.
			else
			{
				// 이전에는 겹쳐있었다.
				if (iter->second)
				{
					m_vecCollider[_Row][i]->EndOverlap(m_vecCollider[_Col][j]);
					m_vecCollider[_Row][i]->SetPenetratedVec(Vec2(0, 0));
					m_vecCollider[_Col][j]->EndOverlap(m_vecCollider[_Row][i]);
					m_vecCollider[_Col][j]->SetPenetratedVec(Vec2(0, 0));
				}

				iter->second = false;
			}
		}
	}	 
}

bool CollisionMgr::IsOverlap(Collider* _Left, Collider* _Right)
{
	Vec2 LeftPos = _Left->GetFinalPos();
	Vec2 LeftScale = _Left->GetScale();

	Vec2 RightPos = _Right->GetFinalPos();
	Vec2 RightScale = _Right->GetScale();

	// 두 충돌체의 중심끼리의 축별 거리
	if (fabs(RightPos.x - LeftPos.x) < (LeftScale.x / 2.f + RightScale.x / 2.f)
		&& fabs(RightPos.y - LeftPos.y) < (LeftScale.y / 2.f + RightScale.y / 2.f))
	{
		float dx = LeftPos.x - RightPos.x;
		float px = (LeftScale.x + RightScale.x) - fabs(dx);

		float dy = LeftPos.y - RightPos.y;
		float py = (LeftScale.y + RightScale.y) - fabs(dy);
		if (px < py) {
			_Left->SetPenetratedVec(Vec2(dx < 0 ? px : -px, 0));
			_Right->SetPenetratedVec(Vec2(dx < 0 ? px : -px, 0));
		}
		else {
			_Left->SetPenetratedVec(Vec2(0, dy < 0 ? py : -py));
			_Right->SetPenetratedVec(Vec2(0, dy < 0 ? py : -py));
		}

		return true;
	}
	
	return false;
}

void CollisionMgr::CollisionCheck(ACTOR_TYPE _Left, ACTOR_TYPE _Right, bool _Check)
{
	UINT Row = _Left;
	UINT Col = _Right;

	if (Col < Row)
	{
		Row = _Right;
		Col = _Left;
	}
	
	// 비트값이 0 이면 1로, 0 이었으면 1
	// m_Matrix[Row] ^= (1 << Col);

	if(_Check)
		m_Matrix[Row] |= (1 << Col);
	else
		m_Matrix[Row] &= ~(1 << Col);
}

