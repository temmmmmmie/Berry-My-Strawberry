#pragma once
#include "UI.h"
class ATexture;

class ImageUI:
    public Widget
{
public:
    ATexture*  m_Tex;
    
public:
    void SetTexture(ATexture* _texture) { m_Tex = _texture; }
    virtual void Tick_UI() override;
    virtual void Render_UI(HDC _dc) override;
    virtual void LBtnClicked() override;
    virtual void LBtnDown_UI() override;

public:
    ImageUI();
    virtual ~ImageUI();
};

