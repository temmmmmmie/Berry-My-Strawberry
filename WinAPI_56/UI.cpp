#include "pch.h"
#include "UI.h"

#include "Camera.h"
#include "KeyMgr.h"

Widget::Widget()
	: m_ParentUI(nullptr)
	, m_MouseOn(false)
	, m_PrevMouseOn(false)
	, m_LBtnDown(false)
	, m_Mode(SCREEN)
{
}

Widget::~Widget()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		delete m_vecChildUI[i];
	}
}

void Widget::AddChildUI(Widget* _OtherUI)
{
	m_vecChildUI.push_back(_OtherUI);
	_OtherUI->m_ParentUI = this;
}

Vec2 Widget::GetUIRenderPos()
{
	if (m_Mode == SCREEN)
	{
		return m_FinalPos;
	}

	else // WORLD
	{
		return Camera::GetInst()->GetRenderPos(GetFinalPos());
	}
}

void Widget::Tick()
{
	// UI 가 항상 해야 할 일
	// FinalPos 계산
	CalcFinalPos();

	// 마우스 감지
	CalcMousePos();

	// 마우스 왼쪽 눌림 해제 체크
	if (KEY_RELEASED(LBTN))
		m_LBtnDown = false;

	// UI 가 할일 수행
	Tick_UI();

	// 자식 UI 들 할일 수행
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Tick();
	}
}

void Widget::Render(HDC _dc)
{
	// 자기자신 렌더링
	Render_UI(_dc);

	// 자식 UI 들 렌더링
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Render(_dc);
	}
}



void Widget::CalcFinalPos()
{
	m_FinalPos = GetPos();

	if (m_ParentUI)
	{
		m_FinalPos += m_ParentUI->GetFinalPos();
	}
}

void Widget::CalcMousePos()
{
	Vec2 vMousePos = KeyMgr::GetInst()->GetMousePos();

	// UI Mode 에 따른 UI 의 렌더링 위치를 가져온다.
	Vec2 vRenderPos = GetUIRenderPos();

	// 이전 프레임에 마우스가 UI 위에 있었는지 기억해둔다.
	m_PrevMouseOn = m_MouseOn;

	// UI 렌더링 위치와, 마우스 좌표를 비교해서 마우스가 UI 안에 있는지 밖에 있는지 체크한다.
	if (vRenderPos.x <= vMousePos.x && vMousePos.x <= vRenderPos.x + GetScale().x
		&& vRenderPos.y <= vMousePos.y && vMousePos.y <= vRenderPos.y + GetScale().y)
	{
		m_MouseOn = true;
	}
	else
	{
		m_MouseOn = false;
	}
}