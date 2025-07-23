#pragma once

#include "Base.h"

class Component;
class Collider;

// 물체의 최소 단위
// 파생될 수많은 실제 사용할 Actor 류 클래스들의 공통 부모부분
class Actor
	: public Base
{
private:
	Vec2				m_Pos;	 	 // Actor 의 위치값
	Vec2				m_Scale;	 // Actor 의 크기
	vector<Component*>	m_vecCom;	 // Actor 가 소유한 컴포넌트들

	ACTOR_TYPE			m_ActorType; // Level 내에서의 소속그룹
	bool				m_Dead;		 // 삭제 예정상태

public:
	template<typename T>
	T* AddComponent(T* _Component);

	Component* GetComponent(const wstring& _Name);
	Component* GetComponent(COMPONENT_TYPE _Type);

	template<typename T>
	T* GetComponent();

	bool IsDead() { return m_Dead; }

public:	
	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
	Vec2 GetPos() { return m_Pos; }
	Vec2 GetRenderPos();
	Vec2 GetScale() { return m_Scale; }
	ACTOR_TYPE GetActorType() { return m_ActorType; }

	void Destroy();

public:	
	// Level 이 시작될때 or 시작한 레벨에 Actor 가 합류할 때 호출되는 함수
	virtual void Begin() {}
	// Actor 가 매 프레임마다 할 일
	virtual void Tick() = 0;

	// Actor 가 소유한 Component 들이 매 프레임마다 할 일
	virtual void FinalTick();

	// Actor 가 자기자신을 화면(백버퍼)에 그리는 함수
	virtual void Render(HDC _dc);


	virtual void BeginOverlap(class Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) {}
	virtual void Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) {}
	virtual void EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) {}


public:
	Actor();
	virtual ~Actor();

	friend class Level;
	friend class EventMgr;
};

template<typename T>
T* Actor::AddComponent(T* _Component)
{
	m_vecCom.push_back(_Component);

	_Component->m_Owner = this;

	return _Component;
}



template<typename T>
T* Actor::GetComponent()
{	
	for (size_t i = 0; i < m_vecCom.size(); ++i)
	{
		T* pFind = dynamic_cast<T*>(m_vecCom[i]);

		if (nullptr != pFind)
		{
			return pFind;
		}
	}

	return nullptr;
}