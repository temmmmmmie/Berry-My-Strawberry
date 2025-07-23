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
	// UI �� �׻� �ؾ� �� ��
	// FinalPos ���
	CalcFinalPos();

	// ���콺 ����
	CalcMousePos();

	// ���콺 ���� ���� ���� üũ
	if (KEY_RELEASED(LBTN))
		m_LBtnDown = false;

	// UI �� ���� ����
	Tick_UI();

	// �ڽ� UI �� ���� ����
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Tick();
	}
}

void Widget::Render(HDC _dc)
{
	// �ڱ��ڽ� ������
	Render_UI(_dc);

	// �ڽ� UI �� ������
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

	// UI Mode �� ���� UI �� ������ ��ġ�� �����´�.
	Vec2 vRenderPos = GetUIRenderPos();

	// ���� �����ӿ� ���콺�� UI ���� �־����� ����صд�.
	m_PrevMouseOn = m_MouseOn;

	// UI ������ ��ġ��, ���콺 ��ǥ�� ���ؼ� ���콺�� UI �ȿ� �ִ��� �ۿ� �ִ��� üũ�Ѵ�.
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