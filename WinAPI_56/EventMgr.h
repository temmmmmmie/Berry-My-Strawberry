#pragma once

class Actor;

class EventMgr
{
	SINGLE(EventMgr);
private:
	vector<tEventInfo>	m_vecEvent;
	vector<Actor*>		m_Garbage;


public:
	void AddEvent(tEventInfo _Info) { m_vecEvent.push_back(_Info); }
	void ClearGarbage();

public:
	void Tick();
};

