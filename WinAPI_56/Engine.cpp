#include "pch.h"
#include "Engine.h"

#include "KeyMgr.h"
#include "TimeMgr.h"
#include "LevelMgr.h"
#include "PathMgr.h"
#include "AssetMgr.h"
#include "CollisionMgr.h"
#include "RenderMgr.h"
#include "EventMgr.h"
#include "Camera.h"
#include "UIMgr.h"
#include "TextMgr.h"
#include "GameMgr.h"
#include "ShaderLoader.h"

Engine::Engine()
	: m_hInst(nullptr)
	, m_hMainWnd(nullptr)
	, m_Resolution{}
	, m_MainDC(nullptr)
	, m_Pen{}
	, m_Brush{}
{
}

Engine::~Engine()
{
	for (UINT i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_Pen[i]);
	}

	for (UINT i = 0; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		if (i == (UINT)BRUSH_TYPE::HOLLOW)
			continue;

		DeleteObject(m_Brush[i]);
	}

	DeleteObject(m_BackBufferBit);
	DeleteDC(m_BackBufferDC);

	RenderMgr::GetInst()->Release();
	ReleaseDC(GetActiveWindow(), m_MainDC);
}



void Engine::Init(HINSTANCE _Inst, HWND _hWnd, HWND _Preview, HWND _ColRow, UINT _Width, UINT _Height)
{
	m_hInst = _Inst;
	m_hMainWnd = _hWnd;

	m_PreviewWin = _Preview;
	m_ColRowWin = _ColRow;
	
	// 요청한 수치로 해상도 변경
	ChangeResolution(_Width, _Height);	

	// DC 
	// 그림을 그릴 목적지 (비트맵)
	// 비트맵  : 윈도우 비트맵
	// 펜      : Black
	// 브러쉬  : White
	m_MainDC = GetDC(m_hMainWnd);

	// 백버퍼 생성
	// 화면 해상도랑 동일한 크기의 비트맵 생성
	m_BackBufferBit = CreateCompatibleBitmap(m_MainDC, _Width, _Height);

	// 백버퍼 비트맵을 목적지로 지정하는 DC 생성
	// 비트맵  : 1 픽셀 비트맵
	// 펜      : Black
	// 브러쉬  : White	
	m_BackBufferDC = CreateCompatibleDC(m_MainDC);
	DeleteObject(SelectObject(m_BackBufferDC, m_BackBufferBit));

	// GDIObject Pen, Brush 생성
	CreateGDIObject();

	// Manager 초기화
	RenderMgr::GetInst()->InitOpenGL(_hWnd);
	PathMgr::GetInst()->Init();
	AssetMgr::GetInst()->Init();
	ShaderLoader::GetInst()->init();
	LevelMgr::GetInst()->Init();
	Camera::GetInst()->init();
	TextMgr::GetInst()->init();
}

void Engine::Progress()
{	
	// 연산 수행
	TimeMgr::GetInst()->Tick();
	KeyMgr::GetInst()->Tick();
	Camera::GetInst()->Tick();
	GameMgr::GetInst()->tick();
	
	// UIMgr 업데이트
	UIMgr::GetInst()->Tick();
	LevelMgr::GetInst()->Tick();

	// 충돌검사
	CollisionMgr::GetInst()->Tick();

	// 렌더링
	RenderMgr::GetInst()->Render();

	// Event 처리
	EventMgr::GetInst()->Tick();

}


void Engine::ChangeResolution(float _Width, float _Height)
{

	UINT dpi = GetDpiForSystem(); // 또는 GetDpiForWindow(hwnd)
	RECT rt = { 0, 0, _Width, _Height };
	AdjustWindowRectExForDpi(&rt, WS_OVERLAPPEDWINDOW, FALSE, 0, dpi);

	// 윈도우의 좌상단 좌표와, 가로세로 길이를 설정해 줄 수 있는 함수
	SetWindowPos(m_hMainWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	RECT rc;
	GetClientRect(m_hMainWnd, &rc);  // hWnd: 네 윈도우 핸들
	float width_ = rc.right - rc.left;
	float height_ = rc.bottom - rc.top;
	
	m_Resolution = Vec2{ width_ , height_ };
}

void Engine::CreateGDIObject()
{
	// Pen 생성
	m_Pen[(UINT)PEN_TYPE::RED]		= CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_Pen[(UINT)PEN_TYPE::GREEN]	= CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_Pen[(UINT)PEN_TYPE::BLUE]		= CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_Pen[(UINT)PEN_TYPE::GRAY]		= CreatePen(PS_SOLID, 1, RGB(100, 100, 100));
	m_Pen[(UINT)PEN_TYPE::WHITE]	= CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	m_Pen[(UINT)PEN_TYPE::MAGENTA]	= CreatePen(PS_SOLID, 1, RGB(255, 0, 255));

	// Brush 생성
	m_Brush[(UINT)BRUSH_TYPE::RED]		= CreateSolidBrush(RGB(255, 0, 0));
	m_Brush[(UINT)BRUSH_TYPE::GREEN]	= CreateSolidBrush(RGB(0, 255, 0));
	m_Brush[(UINT)BRUSH_TYPE::BLUE]		= CreateSolidBrush(RGB(0, 0, 255));
	m_Brush[(UINT)BRUSH_TYPE::GRAY]		= CreateSolidBrush(RGB(127, 127, 127));
	m_Brush[(UINT)BRUSH_TYPE::MAGENTA]	= CreateSolidBrush(RGB(255, 0, 255));
	m_Brush[(UINT)BRUSH_TYPE::HOLLOW]   = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
}