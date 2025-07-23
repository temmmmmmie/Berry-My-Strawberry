#pragma once


class Base
{
private:
	static UINT g_GlobalID;

private:
	wstring		m_Name;	// 객체별로 가질 수 있는 이름
	const UINT	m_ID;	// 객체마다 고유한 식별 ID

public:
	void SetName(const wstring& _Name) { m_Name = _Name;  }
	const wstring& GetName() { return m_Name; }

	UINT GetID() { return m_ID; }

public:
	Base();
	virtual ~Base();
};

