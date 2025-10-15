#pragma once

#include "Base.h"

class Actor;

class Level
	: public Base
{
private:
	vector<Actor*>	m_vecActor[ACTOR_END];

public:
	void MoveActor(ACTOR_TYPE _from, ACTOR_TYPE _to);
	void AddActor(ACTOR_TYPE _Idx, Actor* _Actor);
	const vector<Actor*>& GetActor(ACTOR_TYPE _Type) { return m_vecActor[_Type]; }

public:
	virtual void Begin();			// ������ ������ ��
	virtual void Tick();			// �� �����Ӹ��� �����ȿ� �ִ� Actor ���� �� ���� �����ϰ� ����
	virtual void FinalTick();		// �� �����Ӹ��� �����ȿ� �ִ� Actor ���� ������ Component ���� �� ���� �����ϰ� ����
	virtual void Render(HDC _dc);   // �� �����Ӹ��� �����ȿ� �ִ� Actor ���� ȭ�鿡 �׸�
	virtual void End() = 0;			// ������ ����� �� ȣ���

protected:
	void ClearActor(ACTOR_TYPE _Type);
	void ClearAllActor();

public:
	Level();
	virtual ~Level();
};