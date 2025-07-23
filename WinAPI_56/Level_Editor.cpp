#include "pch.h"
#include "Level_Editor.h"
#include "Text.h"

#include "PathMgr.h"
#include "LevelMgr.h"
#include "Camera.h"

#include "resource.h"
#include "Engine.h"
#include "KeyMgr.h"
#include "AssetMgr.h"
#include "ASprite.h"

#include "VideoPlayer.h"
#include "TileRender.h"
#include "TileActor.h"

#include "PanelUI.h"
#include "BtnUI.h"

#include "ASound.h"


Level_Editor::Level_Editor()
	: m_hMenu(nullptr)
	, m_TileActor(nullptr)
{
	// 에디터레벨 전용 메뉴바 생성
	m_hMenu = LoadMenu(Engine::GetInst()->GetProcessInst(), MAKEINTRESOURCEW(MENU_EDITOR));
}

Level_Editor::~Level_Editor()
{
	DestroyMenu(m_hMenu);
}

void Level_Editor::Begin()
{

	//VideoPlayer::GetInst()->Play(L"MovingCrow");


	// 메뉴 부착
	SetMenu(Engine::GetInst()->GetMainWinow(), m_hMenu);

	// 해상도 재 조정
	Vec2 vResolution = Engine::GetInst()->GetResolution();
	Engine::GetInst()->ChangeResolution((UINT)vResolution.x, (UINT)vResolution.y);

	// TileActor 하나 생성
	m_TileActor = new TileActor;
	m_TileActor->GetTileRender()->SetColRow(5, 5);
	AddActor(ACTOR_TYPE::TILE, m_TileActor);

	// UI 생성	
	CreateEditorUI();

	// 모든 액터에 Begin 호출
	Level::Begin();
}

void Level_Editor::Tick()
{
	Level::Tick();
	if (KEY_TAP(KEY::LBTN))
	{
		// 마우스 좌표를 알아낸다.
		Vec2 vMousePos = KeyMgr::GetInst()->GetMousePos();

		// 마우스 좌표가 가리키는 곳의 실제 좌표를 알아낸다
		vMousePos = Camera::GetInst()->GetRealPos(vMousePos);

		// 마우스가 클릭한 지점의 타일이 누군지 알아낸다.
		Vec2 vTileSize = m_TileActor->GetTileRender()->GetTileSize();

		// 마우스위치와 타일액터의 차이값을 구한다.
		Vec2 vDiff = vMousePos - m_TileActor->GetPos();

		// 차이값을 타일사이즈로 나눠서 몇행 몇열 타일을 클릭했는지를 알아낸다.
		int Col = (int)vDiff.x / (int)vTileSize.x;
		int Row = (int)vDiff.y / (int)vTileSize.y;

		// 타일 범위 밖을 클릭했을 경우 예외처리
		int MaxCol = m_TileActor->GetTileRender()->GetMaxCol();
		int MaxRow = m_TileActor->GetTileRender()->GetMaxRow();

		if (0 <= vDiff.x && Col < MaxCol
			&& 0 <= vDiff.y && Row < MaxRow)
		{
			wstring Key = L"TileSprite_10";
			wstring Path = L"Sprite\\";
			ASprite* pSprite = AssetMgr::GetInst()->LoadSprite(Key, Path + Key + L".sprite");
			m_TileActor->GetTileRender()->SetSprite(Col, Row, pSprite);
		}
	}
}

void Level_Editor::End()
{
	// 모든 액터 제거
	ClearAllActor();

	// 메뉴바 제거
	SetMenu(Engine::GetInst()->GetMainWinow(), nullptr);

	// 해상도 재 조정
	Vec2 vResolution = Engine::GetInst()->GetResolution();
	Engine::GetInst()->ChangeResolution((UINT)vResolution.x, (UINT)vResolution.y);
}

void Level_Editor::SaveTile()
{
	// 파일경로를 저장할 배열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};
	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 고른 경로를 받아낼 목적지
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = PathMgr::GetInst()->GetContentPath().c_str();

	if (GetSaveFileName(&Desc))
	{
		m_TileActor->GetTileRender()->Save(szFilePath);
	}
}

void Level_Editor::LoadTile()
{
	// 파일경로를 저장할 배열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};
	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 고른 경로를 받아낼 목적지
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = PathMgr::GetInst()->GetContentPath().c_str();

	if (GetOpenFileName(&Desc))
	{
		// LevelEidtor 에 있는 TileActor의 TileRender 컴포넌트 정보를 파일로부터 불러온다.		
		m_TileActor->GetTileRender()->Load(szFilePath);
	}
}
void Level_Editor::CreateEditorUI()
{
	Vec2 vResolution = Engine::GetInst()->GetResolution();

	{
		PanelUI* pPanel = new PanelUI;
		pPanel->SetName(L"Panel 1");
		pPanel->SetUIMode(UI_MODE::SCREEN);
		pPanel->SetScale(Vec2(400.f, 500.f));
		pPanel->SetPos(Vec2(vResolution.x - pPanel->GetScale().x - 10.f, 10.f));

		BtnUI* pBtnUI = new BtnUI;
		pBtnUI->SetName(L"Save Button");
		//pBtnUI->SetCallBack(::SaveTile);
		pBtnUI->SetDelegate(this, (MEM_FUNC)&Level_Editor::SaveTile);
		pBtnUI->SetUIMode(SCREEN);
		pBtnUI->SetScale(Vec2(120.f, 50.f));
		pBtnUI->SetPos(Vec2(10.f, 10.f));
		pPanel->AddChildUI(pBtnUI);

		pBtnUI = new BtnUI;
		pBtnUI->SetName(L"Load Button");
		//pBtnUI->SetCallBack(::LoadTile);
		pBtnUI->SetDelegate(this, (MEM_FUNC)&Level_Editor::LoadTile);
		pBtnUI->SetUIMode(SCREEN);
		pBtnUI->SetScale(Vec2(120.f, 50.f));
		pBtnUI->SetPos(Vec2(pPanel->GetScale().x - 10.f - pBtnUI->GetScale().x, 10.f));
		pPanel->AddChildUI(pBtnUI);

		//Text* pText = new Text(L"모든 S의 운명은 비극적이였다", Fonttype::HeirofLightBold, 0.3f, 0, 0.3f);
		//pText->SetName(L"Text");
		//pText->SetUIMode(SCREEN);
		//pText->SetScale(Vec2(0.4f, 0.4f));
		//pText->SetPos(Vec2(23.f, 65.f));
		//pPanel->AddChildUI(pText);

		AddActor(ACTOR_TYPE::UI, pPanel);

	}

	{
		PanelUI* pPanel = new PanelUI;
		pPanel->SetName(L"Panel 2");
		pPanel->SetUIMode(UI_MODE::SCREEN);
		pPanel->SetScale(Vec2(400.f, 500.f));
		pPanel->SetPos(Vec2(vResolution.x - pPanel->GetScale().x - 10.f - 300, 10.f + 100));

		BtnUI* pBtnUI = new BtnUI;
		pBtnUI->SetName(L"Save Button");
		//pBtnUI->SetCallBack(::SaveTile);
		pBtnUI->SetDelegate(this, (MEM_FUNC)&Level_Editor::SaveTile);
		pBtnUI->SetUIMode(SCREEN);
		pBtnUI->SetScale(Vec2(120.f, 50.f));
		pBtnUI->SetPos(Vec2(10.f, 10.f));
		pPanel->AddChildUI(pBtnUI);

		pBtnUI = new BtnUI;
		pBtnUI->SetName(L"Load Button");
		//pBtnUI->SetCallBack(::LoadTile);
		pBtnUI->SetDelegate(this, (MEM_FUNC)&Level_Editor::LoadTile);
		pBtnUI->SetUIMode(SCREEN);
		pBtnUI->SetScale(Vec2(120.f, 50.f));
		pBtnUI->SetPos(Vec2(pPanel->GetScale().x - 10.f - pBtnUI->GetScale().x, 10.f));
		pPanel->AddChildUI(pBtnUI);

		AddActor(ACTOR_TYPE::UI, pPanel);
	}



}

// ==========
// 메뉴바 버튼
// ==========
INT_PTR CALLBACK TileColRow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void SaveTile();
void LoadTile();

LRESULT CALLBACK MenuButtonCallBack(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInst = Engine::GetInst()->GetProcessInst();

	int wmId = LOWORD(wParam);

	UINT iValue = 0;

	// 메뉴 선택을 구문 분석합니다:
	switch (wmId)
	{
	break;
	case ID_TILE_COLROW:
	{
		iValue = DialogBox(hInst, MAKEINTRESOURCE(DLG_TILE_COLROW), hWnd, TileColRow);
	}
	break;
	case ID_TILE_SAVE:
	{
		SaveTile();
	}
	break;
	case ID_TILE_LOAD:
	{
		LoadTile();
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

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

// ==========================
// Tile ColRow Dialog 프로시저
// ==========================
INT_PTR CALLBACK TileColRow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// Editor Control 에 입력된 숫자를 알아낸다.
			int Col = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int Row = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);
			if (Col == 0) Col = 1;
			if (Row == 0) Row = 1;

			// EditorLevel 의 TileActor 의 TileRender 컴포넌트에 Col, Row 를 세팅해준다.
			Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
			Level_Editor* pEditorLevel = dynamic_cast<Level_Editor*>(pCurLevel);
			assert(pEditorLevel);

			pEditorLevel->GetTileActor()->GetTileRender()->SetColRow(Col, Row);

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
void SaveTile()
{
	// 파일경로를 저장할 배열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};
	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 고른 경로를 받아낼 목적지
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = PathMgr::GetInst()->GetContentPath().c_str();

	if (GetSaveFileName(&Desc))
	{
		// LevelEidtor 에 있는 TileActor의 TileRender 컴포넌트 정보를 파일로 저장한다.
		Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
		Level_Editor* pEditorLevel = dynamic_cast<Level_Editor*>(pCurLevel);
		assert(pEditorLevel);

		pEditorLevel->GetTileActor()->GetTileRender()->Save(szFilePath);
	}
}

void LoadTile()
{
	// 파일경로를 저장할 배열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};
	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 고른 경로를 받아낼 목적지
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = PathMgr::GetInst()->GetContentPath().c_str();

	if (GetOpenFileName(&Desc))
	{
		// LevelEidtor 에 있는 TileActor의 TileRender 컴포넌트 정보를 파일로부터 불러온다.		
		Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
		Level_Editor* pEditorLevel = dynamic_cast<Level_Editor*>(pCurLevel);
		assert(pEditorLevel);

		pEditorLevel->GetTileActor()->GetTileRender()->Load(szFilePath);
	}
}
