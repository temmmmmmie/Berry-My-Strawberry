#pragma once


enum KEY
{
	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	W,
	S,
	A,
	D,

	Z,
	X,
	C,
	V,

	ENTER,
	ALT,
	CTRL,
	SPACE,
	LSHIFT,
	ESC,
	END,

	LEFT,
	RIGHT,
	UP,
	DOWN,

	LBTN,
	RBTN,

	KEY_END,
};

enum KEY_STATE
{
	NONE,
	TAP,
	PRESSED,
	RELEASED,
};

struct tKeyInfo
{
	KEY_STATE State;
	bool	  PrevPressed;
	// 마우스 이동 방향벡터
};

class KeyMgr	
{
	SINGLE(KeyMgr)
private:
	vector<tKeyInfo>	m_vecKeys;
	Vec2				m_MousePos;			// 이번 프레임 마우스 좌표
	Vec2				m_PrevMouse;		// 이전 프레임 마우스 좌표
	Vec2				m_MouseDragDir;
public:
	KEY_STATE GetKeyState(KEY _Key) { return m_vecKeys[_Key].State; }

	Vec2 GetMousePos() { return m_MousePos; }
	Vec2 GetPrevMousePos() { return m_PrevMouse; }
	Vec2 GetMouseDragDir() { return m_MouseDragDir; }
public:
	void Tick();
};

