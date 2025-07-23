#pragma once
#include "UI.h"


typedef void(Base::* MEM_FUNC)(void);
class ATexture;
class BtnUI :
    public Widget
{
public:
    PEN_TYPE    m_Type;

    // 전역 함수 포인터 (CallBack)
    void(*m_CallBack)(void);

    // Delegate
    Base* m_Inst;
    MEM_FUNC    m_MemFunc;

    ATexture* m_tex;
    bool m_Enabled;
public:
    void SetCallBack(void(*_Func)(void)) { m_CallBack = _Func; }
    void SetDelegate(Base* _Inst, MEM_FUNC _memFunc) { m_Inst = _Inst;  m_MemFunc = _memFunc; }

public:
    virtual void Tick_UI() override;
    virtual void Render_UI(HDC _dc) override;

    virtual void BeginHover() override;
    virtual void Hover() override;
    virtual void EndHover() override;

    virtual void LBtnDown_UI() override;
    virtual void LBtnRelease_UI() override;
    virtual void LBtnClicked() override;

public:
    BtnUI();
    BtnUI(ATexture* _tex);
    virtual ~BtnUI();
};

