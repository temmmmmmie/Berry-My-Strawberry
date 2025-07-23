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

	float			m_DeltaTime; // 1 프레임 수행하는데 걸리는 시간
	float			m_AccTime;	 // 누적 시간



public:
	float GetDeltaTime() { return m_DeltaTime; }
	float GetFrameCount() { return m_FrameCount; }

public:
	void Tick();
	void Render(HDC _dc);



};

