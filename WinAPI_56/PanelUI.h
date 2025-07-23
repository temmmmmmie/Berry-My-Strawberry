#pragma once
#include "UI.h"

class ATexture;
class PanelUI :
    public Widget
{
private:
    Vec2        m_PrevPressedPos;
    ATexture*    m_tex;

public:
    virtual void Tick_UI() override;
    virtual void Render_UI(HDC _dc) override;
    virtual void LBtnClicked() override;
    virtual void LBtnDown_UI() override;




public:
    PanelUI();
    PanelUI(ATexture* _tex);
    virtual ~PanelUI();
};

