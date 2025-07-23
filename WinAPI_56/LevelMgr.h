#pragma once


class Level;

class LevelMgr
{
	SINGLE(LevelMgr);
public:
	Level* m_arrLevel[(UINT)LEVEL_TYPE::END];  // ��ü ���� ���
	Level*		m_CurLevel;	// ���� �������� ����


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

