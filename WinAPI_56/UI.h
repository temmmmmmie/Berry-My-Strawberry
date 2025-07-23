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
    Widget* m_ParentUI;     // �θ� UI
    vector<Widget*> m_vecChildUI;   // �ڽ� UI��

    Vec2            m_FinalPos;     // �θ� UI ��ġ + �ڽ��� ��ġ == ���� ��ġ
    bool            m_MouseOn;      // �̹� �����ӿ� ���콺�� �ش� UI ���� �ִ���
    bool            m_PrevMouseOn;  // ���� �����ӿ� ���콺�� �ش� UI ���� �־�����
    bool            m_LBtnDown;     // ���콺 ������ ���� ����

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

