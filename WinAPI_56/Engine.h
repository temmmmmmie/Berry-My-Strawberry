#pragma once


// �ھ� �ٽ� ��� Ŭ����
class Engine
{
	SINGLE(Engine);
private:
	HINSTANCE	m_hInst;		// ���μ��� �ڵ�
	HWND		m_hMainWnd;		// ���������� �ڵ�
	Vec2		m_Resolution;	// ������ �ػ�(����, ���� �ȼ� ��)

	HDC			m_MainDC;		// DeviceContext, ������ ���� ��� ��� ��ü
	HGLRC		m_MainGLRC;		// DeviceContext, ������ ���� ��� ��� ��ü

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

