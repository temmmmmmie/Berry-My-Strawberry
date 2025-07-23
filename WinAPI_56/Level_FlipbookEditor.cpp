#include "pch.h"
#include "Level_FlipbookEditor.h"

#include "RenderMgr.h"
#include <string>
#include "resource.h"
#include "PathMgr.h"
#include "LevelMgr.h"
#include "KeyMgr.h"
#include "AssetMgr.h"
#include "Camera.h"
#include "Engine.h"

#include "FlipbookPreview.h"
#include "SpriteRender.h"
#include "SpriteActor.h"
#include "AFlipbook.h"
#include "ASprite.h"
#include "ATexture.h"
#include "ASound.h"


Level_FlipbookEditor::Level_FlipbookEditor()
	: EditorState(SPRITEEDIT),
	m_hMenu(nullptr),
	m_SpriteActor(nullptr),
	m_FlipbookPreview(nullptr),
	m_RealMouseAnchor(Vec2(0,0))
{
	m_hMenu = LoadMenu(Engine::GetInst()->GetProcessInst(), MAKEINTRESOURCEW(MENU_EDITOR));
}

Level_FlipbookEditor::~Level_FlipbookEditor()
{
	DestroyMenu(m_hMenu);
}
void Level_FlipbookEditor::Begin()
{
	// 메뉴 부착
	SetMenu(Engine::GetInst()->GetMainWinow(), m_hMenu);

	// 해상도 재 조정
	Vec2 vResolution = Engine::GetInst()->GetResolution();
	Engine::GetInst()->ChangeResolution((UINT)vResolution.x, (UINT)vResolution.y);
	
	m_SpriteActor = new SpriteActor(this);
	m_SpriteRender = m_SpriteActor->GetSpriteRender();
	AddActor(ACTOR_TYPE::FLIPBOOK, m_SpriteActor);

	m_FlipbookPreview = new FlipbookPreview(this, m_SpriteRender->GetFlip());
	AddActor(ACTOR_TYPE::FLIPBOOK, m_FlipbookPreview);
	
	RenderMgr::GetInst()->SetDebugRender(true);
	Level::Begin();
}

void Level_FlipbookEditor::Tick()
{
	if (EditorState == SPRITEEDIT) {

		if (KEY_TAP(KEY::LBTN))
		{
			// 마우스 좌표를 알아낸다.
			Vec2 vMousePos = KeyMgr::GetInst()->GetMousePos();
			m_MouseAnchor = vMousePos;

			m_RealMouseAnchor = Camera::GetInst()->GetRealPos(vMousePos);
		}
		if (KEY_PRESSED(KEY::LBTN))
		{
			// 마우스 좌표를 알아낸다.
			Vec2 vMousePos = KeyMgr::GetInst()->GetMousePos();
			m_MouseScale = m_MouseAnchor - vMousePos;

		}
		if (KEY_RELEASED(KEY::LBTN)) {
			if (m_SpriteRender->GetTex() && m_MouseScale.x < -20) {
				Vec2 resol = Vec2(m_SpriteRender->GetTex()->GetWidth(), m_SpriteRender->GetTex()->GetHeight());
				m_SpriteRender->AddSprite(m_RealMouseAnchor + (resol / 2), -m_MouseScale);
			}
			m_RealMouseAnchor = Vec2(0, 0);
			m_MouseAnchor = Vec2(0, 0);
			m_MouseScale = Vec2(0, 0);
		}

		if (m_MouseAnchor.x != 0) {
			DrawDebugRect(m_MouseAnchor - m_MouseScale / 2, m_MouseScale, PEN_TYPE::GREEN, 0);
		}
	}
	Level::Tick();
}

void Level_FlipbookEditor::End()
{
	// 모든 액터 제거
	ClearAllActor();

	// 메뉴바 제거
	SetMenu(Engine::GetInst()->GetMainWinow(), nullptr);

	// 해상도 재 조정
	Vec2 vResolution = Engine::GetInst()->GetResolution();
	Engine::GetInst()->ChangeResolution((UINT)vResolution.x, (UINT)vResolution.y);
}
void Level_FlipbookEditor::DisplayFPS(int FPS)
{
	std::wstring str = std::to_wstring(FPS);
	SetDlgItemText(Engine::GetInst()->GetPreview(), CUR_IDX, str.c_str());
}
void Level_FlipbookEditor::DisplayOffset(Vec2 _offset)
{
	std::wstring x = std::to_wstring((int)_offset.x);
	std::wstring y = std::to_wstring((int)_offset.y);
	SetDlgItemText(Engine::GetInst()->GetPreview(), OFFSET_X, x.c_str());
	SetDlgItemText(Engine::GetInst()->GetPreview(), OFFSET_Y, y.c_str());
}
void Level_FlipbookEditor::SaveFlip()
{
	// 파일경로를 저장할 배열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};
	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 고른 경로를 받아낼 목적지
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Flipbook\0*.flip\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = PathMgr::GetInst()->GetContentPath().c_str();

	

	if (GetOpenFileName(&Desc))
	{
		m_SpriteRender->Save(szFilePath, L"FUCK");
	}
}
void Level_FlipbookEditor::LoadFlip()
{
	// 파일경로를 저장할 배열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};
	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 고른 경로를 받아낼 목적지
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Flipbook\0*.flip\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = PathMgr::GetInst()->GetContentPath().c_str();

	if (GetOpenFileName(&Desc))
	{
		m_SpriteRender->Load(szFilePath);
		m_FlipbookPreview->SetFlip(m_SpriteRender->GetFlip());
	}
}

void LoadFlip();
void SaveFlip();
void NewFlip();
LRESULT CALLBACK MenuButtonCallBackFlip(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInst = Engine::GetInst()->GetProcessInst();

	int wmId = LOWORD(wParam);

	UINT iValue = 0;

	// 메뉴 선택을 구문 분석합니다:
	switch (wmId)
	{
	case ID_GRID:
	{
		Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
		Level_FlipbookEditor* pEditorLevel = dynamic_cast<Level_FlipbookEditor*>(pCurLevel);
		assert(pEditorLevel);
		pEditorLevel->SetFlipEditorState(SPRITEEDIT);

		ShowWindow(Engine::GetInst()->GetColRow(), SW_SHOW);

	}
	break;
	case ID_NEW_FLIP:
	{
		NewFlip();
	}
	break;
	case ID_SAVEFLIPBOOK:
	{
		SaveFlip();
	}
	break;
	case ID_LOADFLIPBOOK:
	{

		LoadFlip();
	}
	break;
	case ID_TILEEDIT:
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}
	break;
	case ID_FLIPBOOK:
	{
		ChangeLevel(LEVEL_TYPE::FLIPBOOKEDIT);
	}
	break;
	case ID_PREVIEW:
	{
		Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
		Level_FlipbookEditor* pEditorLevel = dynamic_cast<Level_FlipbookEditor*>(pCurLevel);
		assert(pEditorLevel);
		pEditorLevel->SetFlipEditorState(FLIPPREVIEW);
		Camera::GetInst()->SetLook(Vec2(0,0));

		ShowWindow(Engine::GetInst()->GetPreview(), SW_SHOW);
		SetDlgItemText(Engine::GetInst()->GetPreview(), PLAY_FPS, L"10");
	}
	break;
	case TO_GAME:
	{
		Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
		Level_FlipbookEditor* pEditorLevel = dynamic_cast<Level_FlipbookEditor*>(pCurLevel);
		assert(pEditorLevel);
		pEditorLevel->GetSpriteActor()->GetSpriteRender()->ClearFlip();
		RenderMgr::GetInst()->SetDebugRender(false);
		AssetMgr::GetInst()->FindSound(L"BGM")->PlayToBGM(true);
		ChangeLevel(LEVEL_TYPE::START);
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

INT_PTR CALLBACK FlipBookColRow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
			Level_FlipbookEditor* pEditorLevel = dynamic_cast<Level_FlipbookEditor*>(pCurLevel);
			assert(pEditorLevel);
			// Editor Control 에 입력된 숫자를 알아낸다.
			int Col = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int Row = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);
			if (Col == 0) Col = 1;
			if (Row == 0) Row = 1;

			// EditorLevel 의 TileActor 의 TileRender 컴포넌트에 Col, Row 를 세팅해준다.

			pEditorLevel->GetSpriteActor()->GetSpriteRender()->SetColRow(Col, Row);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK FlipBookPreview(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);


	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
		Level_FlipbookEditor* pEditorLevel = dynamic_cast<Level_FlipbookEditor*>(pCurLevel);
		assert(pEditorLevel);

		if (LOWORD(wParam) == IDCANCEL)
		{
			pEditorLevel->GetFlipbookPreview()->Stop();
			pEditorLevel->SetFlipEditorState(SPRITEEDIT);


			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		else if (LOWORD(wParam) == PLAY)
		{
			int Fps = GetDlgItemInt(hDlg, PLAY_FPS, nullptr, true);
			pEditorLevel->GetFlipbookPreview()->Play(Fps, 0);
		}
		else if (LOWORD(wParam) == STOP)
		{
			pEditorLevel->GetFlipbookPreview()->Stop();
		}
		else if (LOWORD(wParam) == PREV_FRAME)
		{
			pEditorLevel->GetFlipbookPreview()->PrevFrame();
		}
		else if (LOWORD(wParam) == NEXT_FRAME)
		{
			pEditorLevel->GetFlipbookPreview()->NextFrame();

		}
		else if (LOWORD(wParam) == DELETE_FRAME)
		{
			pEditorLevel->GetFlipbookPreview()->DeleteFrame();
		}
		else if (HIWORD(wParam) == EN_CHANGE && (LOWORD(wParam) == OFFSET_X || LOWORD(wParam) == OFFSET_Y))
		{
			wchar_t bufx[256] = {};
			wchar_t bufy[256] = {};

			GetDlgItemText(hDlg, OFFSET_X, bufx, 256);
			GetDlgItemText(hDlg, OFFSET_Y, bufy, 256);


			pEditorLevel->GetFlipbookPreview()->SetOffset(Vec2(wcstof(bufx, nullptr), wcstof(bufy, nullptr)));
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void NewFlip()
{
	// 파일경로를 저장할 배열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};
	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 고른 경로를 받아낼 목적지
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"PNG\0*.png\0JPG\0*.jpg\0BMP\0*.bmp\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = PathMgr::GetInst()->GetContentPath().c_str();

	if (GetOpenFileName(&Desc))
	{
		// LevelEidtor 에 있는 TileActor의 TileRender 컴포넌트 정보를 파일로부터 불러온다.		
		Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
		Level_FlipbookEditor* pEditorLevel = dynamic_cast<Level_FlipbookEditor*>(pCurLevel);
		assert(pEditorLevel);

		SpriteRender* SpriteRender = pEditorLevel->GetSpriteActor()->GetSpriteRender();
		SpriteRender->ClearFlip();
		SpriteRender->NewFlip(szFilePath);
		pEditorLevel->GetFlipbookPreview()->SetFlip(SpriteRender->GetFlip());
		pEditorLevel->SetFlipEditorState(SPRITEEDIT);
		
	}
}
void LoadFlip()
{
	// 파일경로를 저장할 배열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};
	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 고른 경로를 받아낼 목적지
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Flipbook\0*.flip\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = PathMgr::GetInst()->GetContentPath().c_str();

	if (GetOpenFileName(&Desc))
	{
		// LevelEidtor 에 있는 TileActor의 TileRender 컴포넌트 정보를 파일로부터 불러온다.		
		Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
		Level_FlipbookEditor* pEditorLevel = dynamic_cast<Level_FlipbookEditor*>(pCurLevel);
		assert(pEditorLevel);

		SpriteRender* SpriteRender = pEditorLevel->GetSpriteActor()->GetSpriteRender();
		SpriteRender->ClearFlip();
		SpriteRender->Load(szFilePath);
		pEditorLevel->GetFlipbookPreview()->SetFlip(SpriteRender->GetFlip());
	}
}

void SaveFlip()
{
	// 파일경로를 저장할 배열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};
	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 고른 경로를 받아낼 목적지
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Flipbook\0*.flip\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = PathMgr::GetInst()->GetContentPath().c_str();


	if (GetSaveFileName(&Desc))
	{
		// LevelEidtor 에 있는 TileActor의 TileRender 컴포넌트 정보를 파일로 저장한다.
		Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
		Level_FlipbookEditor* pEditorLevel = dynamic_cast<Level_FlipbookEditor*>(pCurLevel);
		assert(pEditorLevel);

		pEditorLevel->GetSpriteActor()->GetSpriteRender()->Save(szFilePath, GetFilenameFromPath(szFilePath));
	}
}

