#pragma once

// 경로 관리자
class PathMgr
{
	SINGLE(PathMgr);
private:
	wstring			m_ContentPath;

public:
	void Init();
	const wstring& GetContentPath() { return m_ContentPath; }
};

