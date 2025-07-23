#pragma once


class Base
{
private:
	static UINT g_GlobalID;

private:
	wstring		m_Name;	// ��ü���� ���� �� �ִ� �̸�
	const UINT	m_ID;	// ��ü���� ������ �ĺ� ID

public:
	void SetName(const wstring& _Name) { m_Name = _Name;  }
	const wstring& GetName() { return m_Name; }

	UINT GetID() { return m_ID; }

public:
	Base();
	virtual ~Base();
};

