#pragma once
#include "Actor.h"

enum UI_MODE
{
    SCREEN,
    WORLD,
};


class Widget :
    public Actor
{
private:
    Widget* m_ParentUI;     // 부모 UI
    vector<Widget*> m_vecChildUI;   // 자식 UI들

    Vec2            m_FinalPos;     // 부모 UI 위치 + 자신의 위치 == 최종 위치
    bool            m_MouseOn;      // 이번 프레임에 마우스가 해당 UI 위에 있는지
    bool            m_PrevMouseOn;  // 이전 프레임에 마우스가 해당 UI 위에 있었는지
    bool            m_LBtnDown;     // 마우스 왼쪽이 눌린 상태

    UI_MODE         m_Mode;

public:
    GET(Vec2, FinalPos);
    void AddChildUI(Widget* _OtherUI);
    void SetUIMode(UI_MODE _Mode) { m_Mode = _Mode; }
    UI_MODE GetUIMode() { return m_Mode; }
    Vec2 GetUIRenderPos();
    bool IsLBtnDown() { return m_LBtnDown; }

public:
    virtual void Tick() override final;
    virtual void Render(HDC _dc) override final;

    virtual void Tick_UI() = 0;
    virtual void Render_UI(HDC _dc) = 0;

    virtual void BeginHover() {}
    virtual void Hover() {}
    virtual void EndHover() {}

    void LbtnDown() { m_LBtnDown = true;  LBtnDown_UI(); }
    virtual void LBtnDown_UI() {}
    virtual void LBtnRelease_UI() {}

    virtual void LBtnClicked() {};

private:
    void CalcFinalPos();
    void CalcMousePos();

public:
    Widget();
    virtual ~Widget();

    friend class UIMgr;
};

