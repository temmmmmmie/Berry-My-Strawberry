#pragma once

// ��� ������
class PathMgr
{
	SINGLE(PathMgr);
private:
	wstring			m_ContentPath;

public:
	void Init();
	const wstring& GetContentPath() { return m_ContentPath; }
};

