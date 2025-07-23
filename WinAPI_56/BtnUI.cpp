#include "pch.h"
#include "BtnUI.h"

#include "Engine.h"

#include "RenderMgr.h"
#include "Camera.h"
#include "PathMgr.h"
#include "LevelMgr.h"
#include "Level_Editor.h"
#include "TileActor.h"
#include "TileRender.h"

#include "ATexture.h"

BtnUI::BtnUI()
	: m_Type(PEN_TYPE::GREEN)
	, m_CallBack(nullptr)
	, m_Inst(nullptr)
	, m_MemFunc(nullptr)
	, m_Enabled(true)
{
}

BtnUI::BtnUI(ATexture* _tex)
	: m_Type(PEN_TYPE::GREEN)
	, m_CallBack(nullptr)
	, m_Inst(nullptr)
	, m_MemFunc(nullptr)
	, m_tex(_tex)
	, m_Enabled(true)
{

}

BtnUI::~BtnUI()
{
}

void BtnUI::Tick_UI()
{

}

void BtnUI::Render_UI(HDC _dc)
{
	if (nullptr == m_tex) {
		Vec2 vRenderPos = GetUIRenderPos();
		Vec2 vScale = GetScale();
		DrawDebugRect(GetUIRenderPos() + GetScale() / 2.f, GetScale(), m_Type, 0.f);
	}
	else
	{
		Vec2 vRenderPos = GetUIRenderPos();
		Vec2 vScale = GetScale();
		RenderMgr::GetInst()->Draw(m_tex, GetUIRenderPos().x + GetScale().x / 2.f, GetUIRenderPos().y + GetScale().y / 2.f, GetScale().x, GetScale().y);
	}
	
}

void BtnUI::BeginHover()
{
	m_Type = PEN_TYPE::RED;
}

void BtnUI::Hover()
{
}

void BtnUI::EndHover()
{
	m_Type = PEN_TYPE::GREEN;
}

void BtnUI::LBtnDown_UI()
{
	m_Type = PEN_TYPE::BLUE;
}

void BtnUI::LBtnRelease_UI()
{
	m_Type = PEN_TYPE::RED;
}

void BtnUI::LBtnClicked()
{
	if (m_Enabled == false) return;
	if (nullptr != m_CallBack)
		m_CallBack();
	
	if (m_Inst && m_MemFunc)
		(m_Inst->*m_MemFunc)();
}