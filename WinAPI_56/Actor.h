#pragma once

#include "Base.h"

class Component;
class Collider;

// ��ü�� �ּ� ����
// �Ļ��� ������ ���� ����� Actor �� Ŭ�������� ���� �θ�κ�
class Actor
	: public Base
{
private:
	Vec2				m_Pos;	 	 // Actor �� ��ġ��
	Vec2				m_Scale;	 // Actor �� ũ��
	vector<Component*>	m_vecCom;	 // Actor �� ������ ������Ʈ��

	ACTOR_TYPE			m_ActorType; // Level �������� �Ҽӱ׷�
	bool				m_Dead;		 // ���� ��������

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
	// Level �� ���۵ɶ� or ������ ������ Actor �� �շ��� �� ȣ��Ǵ� �Լ�
	virtual void Begin() {}
	// Actor �� �� �����Ӹ��� �� ��
	virtual void Tick() = 0;

	// Actor �� ������ Component ���� �� �����Ӹ��� �� ��
	virtual void FinalTick();

	// Actor �� �ڱ��ڽ��� ȭ��(�����)�� �׸��� �Լ�
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