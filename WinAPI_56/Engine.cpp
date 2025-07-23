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
	
	// ��û�� ��ġ�� �ػ� ����
	ChangeResolution(_Width, _Height);	

	// DC 
	// �׸��� �׸� ������ (��Ʈ��)
	// ��Ʈ��  : ������ ��Ʈ��
	// ��      : Black
	// �귯��  : White
	m_MainDC = GetDC(m_hMainWnd);

	// ����� ����
	// ȭ�� �ػ󵵶� ������ ũ���� ��Ʈ�� ����
	m_BackBufferBit = CreateCompatibleBitmap(m_MainDC, _Width, _Height);

	// ����� ��Ʈ���� �������� �����ϴ� DC ����
	// ��Ʈ��  : 1 �ȼ� ��Ʈ��
	// ��      : Black
	// �귯��  : White	
	m_BackBufferDC = CreateCompatibleDC(m_MainDC);
	DeleteObject(SelectObject(m_BackBufferDC, m_BackBufferBit));

	// GDIObject Pen, Brush ����
	CreateGDIObject();

	// Manager �ʱ�ȭ
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
	// ���� ����
	TimeMgr::GetInst()->Tick();
	KeyMgr::GetInst()->Tick();
	Camera::GetInst()->Tick();
	GameMgr::GetInst()->tick();
	
	// UIMgr ������Ʈ
	UIMgr::GetInst()->Tick();
	LevelMgr::GetInst()->Tick();

	// �浹�˻�
	CollisionMgr::GetInst()->Tick();

	// ������
	RenderMgr::GetInst()->Render();

	// Event ó��
	EventMgr::GetInst()->Tick();

}


void Engine::ChangeResolution(float _Width, float _Height)
{

	UINT dpi = GetDpiForSystem(); // �Ǵ� GetDpiForWindow(hwnd)
	RECT rt = { 0, 0, _Width, _Height };
	AdjustWindowRectExForDpi(&rt, WS_OVERLAPPEDWINDOW, FALSE, 0, dpi);

	// �������� �»�� ��ǥ��, ���μ��� ���̸� ������ �� �� �ִ� �Լ�
	SetWindowPos(m_hMainWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	RECT rc;
	GetClientRect(m_hMainWnd, &rc);  // hWnd: �� ������ �ڵ�
	float width_ = rc.right - rc.left;
	float height_ = rc.bottom - rc.top;
	
	m_Resolution = Vec2{ width_ , height_ };
}

void Engine::CreateGDIObject()
{
	// Pen ����
	m_Pen[(UINT)PEN_TYPE::RED]		= CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_Pen[(UINT)PEN_TYPE::GREEN]	= CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_Pen[(UINT)PEN_TYPE::BLUE]		= CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_Pen[(UINT)PEN_TYPE::GRAY]		= CreatePen(PS_SOLID, 1, RGB(100, 100, 100));
	m_Pen[(UINT)PEN_TYPE::WHITE]	= CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	m_Pen[(UINT)PEN_TYPE::MAGENTA]	= CreatePen(PS_SOLID, 1, RGB(255, 0, 255));

	// Brush ����
	m_Brush[(UINT)BRUSH_TYPE::RED]		= CreateSolidBrush(RGB(255, 0, 0));
	m_Brush[(UINT)BRUSH_TYPE::GREEN]	= CreateSolidBrush(RGB(0, 255, 0));
	m_Brush[(UINT)BRUSH_TYPE::BLUE]		= CreateSolidBrush(RGB(0, 0, 255));
	m_Brush[(UINT)BRUSH_TYPE::GRAY]		= CreateSolidBrush(RGB(127, 127, 127));
	m_Brush[(UINT)BRUSH_TYPE::MAGENTA]	= CreateSolidBrush(RGB(255, 0, 255));
	m_Brush[(UINT)BRUSH_TYPE::HOLLOW]   = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
}