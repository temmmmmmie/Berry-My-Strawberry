#include "pch.h"
#include "LevelMgr.h"

#include "Engine.h"
#include "Level.h"

#include "Level_Editor.h"
#include "Level_FlipbookEditor.h"
#include "Level_Tutorial.h"
#include "Level_Start.h"
#include "Level_Stage01.h"
#include "Level_Ending.h"

LevelMgr::LevelMgr()
	: m_CurLevel(nullptr)
{
}

LevelMgr::~LevelMgr()
{
	for (size_t i = 0; i < (UINT)LEVEL_TYPE::END; i++)
	{
		delete m_arrLevel[i];
	}
}

void LevelMgr::Init()
{
	// 레벨 생성
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new Level_Editor;
	m_arrLevel[(UINT)LEVEL_TYPE::FLIPBOOKEDIT] = new Level_FlipbookEditor;
	m_arrLevel[(UINT)LEVEL_TYPE::TUTORIAL] = new Level_Tutorial;
	m_arrLevel[(UINT)LEVEL_TYPE::START] = new Level_Start;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new Level_Stage01;
	m_arrLevel[(UINT)LEVEL_TYPE::ENDING] = new Level_Ending;

	// 시작 레벨을 StartLevel 로 설정
	m_CurLevel = m_arrLevel[(UINT)LEVEL_TYPE::START];

	// 레벨을 플레이
	m_CurLevel->Begin();
}

void LevelMgr::Tick()
{
	m_CurLevel->Tick();		 // Actor 들이 직접 할 일
	m_CurLevel->FinalTick(); // Actor 들이 소유한 Component 들이 할 일
}

void LevelMgr::Render(HDC _DC)
{
	m_CurLevel->Render(_DC);
}


void LevelMgr::ChangeLevel(LEVEL_TYPE _Next)
{
	// 변경하려는 레벨과 현재 레벨이 동일하면 오류
	//assert(m_CurLevel != m_arrLevel[(UINT)_Next]);

	// 이전 레벨을 종료
	m_CurLevel->End();

	// 현재 플레이중인 레벨을 변경
	m_CurLevel = m_arrLevel[(UINT)_Next];

	// 새로운 레벨을 시작함
	m_CurLevel->Begin();
}