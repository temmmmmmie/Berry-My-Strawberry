#pragma once


class Collider;

union COLLIDER_ID
{
	DWORD_PTR ID;

	struct
	{
		UINT Left;
		UINT Right;
	};
};

// 충돌 검사 관리자
class CollisionMgr
{
	SINGLE(CollisionMgr)
private:
	UINT				 m_Matrix[ACTOR_END];
	vector<Collider*>	 m_vecCollider[ACTOR_END];

	map<DWORD_PTR, bool> m_ColInfo;

public:	
	void Tick();
	void CollisionCheck(ACTOR_TYPE _Left, ACTOR_TYPE _Right, bool _Check);
	void CollisionCheckClear() { memset(m_Matrix, 0, sizeof(UINT) * ACTOR_END); }
	void RegisterCollider(Collider* _Collider, ACTOR_TYPE _Type) { m_vecCollider[_Type].push_back(_Collider); }

private:
	void CollisionActor(ACTOR_TYPE _Row, ACTOR_TYPE _Col);

	bool IsOverlap(Collider* _Left, Collider* _Right);
};

