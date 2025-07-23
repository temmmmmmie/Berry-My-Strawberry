#pragma once


class Level;

class LevelMgr
{
	SINGLE(LevelMgr);
public:
	Level* m_arrLevel[(UINT)LEVEL_TYPE::END];  // 전체 레벨 목록
	Level*		m_CurLevel;	// 현재 실행중인 레벨


public:
	Level* GetCurrentLevel() { return m_CurLevel; }

private:
	void ChangeLevel(LEVEL_TYPE _Next);
public:
	void Init();
	void Tick();
	void Render(HDC _DC);

	friend class EventMgr;
};

