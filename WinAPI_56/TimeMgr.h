#pragma once

class TimeMgr
{
	SINGLE(TimeMgr)
private:
	LARGE_INTEGER	m_Frequency;
	LARGE_INTEGER	m_CurCount;
	LARGE_INTEGER	m_PrevCount;

	int				m_FrameCount;
	wchar_t			m_String[256];

	float			m_DeltaTime; // 1 ������ �����ϴµ� �ɸ��� �ð�
	float			m_AccTime;	 // ���� �ð�



public:
	float GetDeltaTime() { return m_DeltaTime; }
	float GetFrameCount() { return m_FrameCount; }

public:
	void Tick();
	void Render(HDC _dc);



};

