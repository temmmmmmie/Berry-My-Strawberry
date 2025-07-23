#pragma once

#include "Base.h"

class Asset
	: public Base
{
private:
	wstring		m_Key;
	wstring		m_RelativePath; // 상대 경로

public:
	const wstring& GetKey() { return m_Key; }
	const wstring& GetRelativePath() { return m_RelativePath; }

	void SetKey(const wstring& _Key) { m_Key = _Key; }
	void SetRelativePath(const wstring& _Path) { m_RelativePath = _Path; }

private:
	virtual int Load(const wstring& _FilePath) = 0;

public:
	Asset();
	virtual ~Asset();
};

