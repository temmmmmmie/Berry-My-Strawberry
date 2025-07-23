#include "pch.h"
#include "UIMgr.h"

#include "LevelMgr.h"
#include "Level.h"
#include "UI.h"

#include "KeyMgr.h"

UIMgr::UIMgr()
	: m_bFocuedChange(false)
{
}

UIMgr::~UIMgr()
{

}

void UIMgr::Tick()
{
	// 현재 레벨에 있는 모든 UI 들을 가져온다.
	Level* pCurLevel = LevelMgr::GetInst()->m_CurLevel;
	if (nullptr == pCurLevel)
		return;

	vector<Actor*>& vecUI = const_cast<vector<Actor*>&>(pCurLevel->GetActor(ACTOR_TYPE::UI));
	if (vecUI.size() == 0) return;
	vector<Actor*>::reverse_iterator riter = vecUI.rbegin();

	// 레벨 벡터안에서 가장 뒤에있는 UI가 FocusedUI 이다.
	m_FocusedUI = dynamic_cast<Widget*>(vecUI.back());
	m_bFocuedChange = false;

	for (; riter != vecUI.rend(); ++riter)
	{
		Widget* pUI = dynamic_cast<Widget*>(*riter);
		assert(pUI);

		// PriorityUI (부모, 자식 포함, 더 우선순위가 높은 UI 를 찾는다)
		pUI = GetPriorityUI(pUI);
		if (nullptr == pUI || m_bFocuedChange)
			continue;

		// LbtnDown
		if (KEY_TAP(LBTN) && pUI->m_MouseOn)
		{
			pUI->LbtnDown();

			//if (m_FocusedUI != dynamic_cast<Widget*>(*riter))
			//{
			//	// 벡터의 가장 뒤로 보낸다.
			//	Widget* pParentUI = dynamic_cast<Widget*>(*riter);

			//	vector<Actor*>::iterator iter = vecUI.erase((riter + 1).base());
			//	vecUI.push_back(pParentUI);

			//	riter = vector<Actor*>::reverse_iterator(iter + 1);
			//}
		}
		// LbtnReleased
		else if (KEY_RELEASED(LBTN) && pUI->m_MouseOn)
		{
			pUI->LBtnRelease_UI();

			// LbtnCliecked
			if (pUI->m_LBtnDown)
			{
				
				pUI->LBtnClicked();
			}
		}

		m_bFocuedChange = true;
	}
}

Widget* UIMgr::GetPriorityUI(Widget* _Parent)
{
	static list<Widget*> queue;
	queue.clear();

	Widget* pPriority = nullptr;


	// 레벨순회
	queue.push_back(_Parent);

	while (!queue.empty())
	{
		Widget* pUI = queue.front();
		queue.pop_front();

		// UI MouseHover 이벤트
		if (!pUI->m_PrevMouseOn && pUI->m_MouseOn)
			pUI->BeginHover();
		else if (pUI->m_MouseOn)
			pUI->Hover();
		else if (pUI->m_PrevMouseOn && !pUI->m_MouseOn)
			pUI->EndHover();

		if (pUI->m_MouseOn)
			pPriority = pUI;

		for (size_t i = 0; i < pUI->m_vecChildUI.size(); ++i)
		{
			queue.push_back(pUI->m_vecChildUI[i]);
		}
	}

	return pPriority;
}