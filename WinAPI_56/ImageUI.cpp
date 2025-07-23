#include "pch.h"
#include "ImageUI.h"
#include "RenderMgr.h"

#include "ATexture.h"

void ImageUI::Tick_UI()
{
}

void ImageUI::Render_UI(HDC _dc)
{
	if (nullptr == m_Tex) return;
	Vec2 renderpos = GetUIRenderPos();
	Vec2 Scale = GetScale();
	RenderMgr::GetInst()->Draw(m_Tex, renderpos.x, renderpos.y, Scale.x, Scale.y);
}

void ImageUI::LBtnClicked()
{
}

void ImageUI::LBtnDown_UI()
{
}

ImageUI::ImageUI()
	:m_Tex(nullptr)
{
}

ImageUI::~ImageUI()
{
}
