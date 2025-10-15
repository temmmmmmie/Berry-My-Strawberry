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
	virtual void Begin();			// 레벨이 시작할 때
	virtual void Tick();			// 매 프레임마다 레벨안에 있는 Actor 들이 할 일을 수행하게 해줌
	virtual void FinalTick();		// 매 프레임마다 레벨안에 있는 Actor 들이 보유한 Component 들이 할 일을 수행하게 해줌
	virtual void Render(HDC _dc);   // 매 프레임마다 레벨안에 있는 Actor 들을 화면에 그림
	virtual void End() = 0;			// 레벨이 종료될 때 호출됨

protected:
	void ClearActor(ACTOR_TYPE _Type);
	void ClearAllActor();

public:
	Level();
	virtual ~Level();
};