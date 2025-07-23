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
	// ���� ����
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new Level_Editor;
	m_arrLevel[(UINT)LEVEL_TYPE::FLIPBOOKEDIT] = new Level_FlipbookEditor;
	m_arrLevel[(UINT)LEVEL_TYPE::TUTORIAL] = new Level_Tutorial;
	m_arrLevel[(UINT)LEVEL_TYPE::START] = new Level_Start;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new Level_Stage01;
	m_arrLevel[(UINT)LEVEL_TYPE::ENDING] = new Level_Ending;

	// ���� ������ StartLevel �� ����
	m_CurLevel = m_arrLevel[(UINT)LEVEL_TYPE::START];

	// ������ �÷���
	m_CurLevel->Begin();
}

void LevelMgr::Tick()
{
	m_CurLevel->Tick();		 // Actor ���� ���� �� ��
	m_CurLevel->FinalTick(); // Actor ���� ������ Component ���� �� ��
}

void LevelMgr::Render(HDC _DC)
{
	m_CurLevel->Render(_DC);
}


void LevelMgr::ChangeLevel(LEVEL_TYPE _Next)
{
	// �����Ϸ��� ������ ���� ������ �����ϸ� ����
	//assert(m_CurLevel != m_arrLevel[(UINT)_Next]);

	// ���� ������ ����
	m_CurLevel->End();

	// ���� �÷������� ������ ����
	m_CurLevel = m_arrLevel[(UINT)_Next];

	// ���ο� ������ ������
	m_CurLevel->Begin();
}