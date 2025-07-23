#include "pch.h"
#include "PanelUI.h"


#include "RenderMgr.h"
#include "ATexture.h"
#include "KeyMgr.h"


PanelUI::PanelUI()
	:m_tex(nullptr)
{
}

PanelUI::PanelUI(ATexture* _tex)
	:m_tex(_tex)
{
}

PanelUI::~PanelUI()
{
}

void PanelUI::Tick_UI()
{
	if (IsLBtnDown())
	{
		Vec2 vCurMousePos = KeyMgr::GetInst()->GetMousePos();
		Vec2 vDiff = vCurMousePos - m_PrevPressedPos;
		SetPos(GetPos() + vDiff);

		m_PrevPressedPos = vCurMousePos;
	}
}

void PanelUI::Render_UI(HDC _dc)
{
	if (nullptr == m_tex) {
		Vec2 vRenderPos = GetUIRenderPos();
		Vec2 vScale = GetScale();
		DrawDebugRect(GetFinalPos() + GetScale() / 2.f, GetScale(), PEN_TYPE::GREEN, 0.f);
	}
	else
	{
		Vec2 vRenderPos = GetUIRenderPos();
		Vec2 vScale = GetScale();
		RenderMgr::GetInst()->Draw(m_tex, vRenderPos.x, vRenderPos.y, m_tex->GetWidth() * vScale.x, m_tex->GetHeight() * vScale.y);
	}


}

void PanelUI::LBtnClicked()
{
	int a = 0;
}

void PanelUI::LBtnDown_UI()
{
	m_PrevPressedPos = KeyMgr::GetInst()->GetMousePos();
}

