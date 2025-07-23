#pragma once


// 코어 핵심 기능 클래스
class Engine
{
	SINGLE(Engine);
private:
	HINSTANCE	m_hInst;		// 프로세스 핸들
	HWND		m_hMainWnd;		// 메인윈도우 핸들
	Vec2		m_Resolution;	// 윈도우 해상도(가로, 세로 픽셀 수)

	HDC			m_MainDC;		// DeviceContext, 렌더링 관련 기능 담당 객체
	HGLRC		m_MainGLRC;		// DeviceContext, 렌더링 관련 기능 담당 객체

	HDC			m_BackBufferDC;
	HBITMAP		m_BackBufferBit;


	HPEN		m_Pen[(UINT)PEN_TYPE::END];
	HBRUSH		m_Brush[(UINT)BRUSH_TYPE::END];

	HWND		m_PreviewWin;
	HWND		m_ColRowWin;

private:
	void CreateGDIObject();

public:
	void Init(HINSTANCE _Inst, HWND _hWnd, HWND _Preview, HWND _ColRow, UINT _Width, UINT _Height);
	void Progress();

	HWND GetMainWinow() { return m_hMainWnd; }
	HWND GetPreview() { return m_PreviewWin; }
	HWND GetColRow() { return m_ColRowWin; }

	HDC GetMainDC() { return m_MainDC; }
	HGLRC GetMainGLRC() { return m_MainGLRC; }
	void SetMainGLRC(HGLRC _HGLRC) { m_MainGLRC = _HGLRC; }
	HDC GetBackBufferDC() { return m_BackBufferDC; }
	Vec2 GetResolution() { return m_Resolution; }
	HINSTANCE GetProcessInst() { return m_hInst; }

	HPEN GetPen(PEN_TYPE _Type) { return m_Pen[(UINT)_Type]; }
	HBRUSH GetBrush(BRUSH_TYPE _Type) { return m_Brush[(UINT)_Type]; }


	void ChangeResolution(float _Width, float _Height);
};

