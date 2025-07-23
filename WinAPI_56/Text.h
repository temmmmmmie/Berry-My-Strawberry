#pragma once
#include "UI.h"
#include "TextMgr.h"
class Text:
	public Widget
{
private:
	Fonttype m_Fonttype;
	float m_FontSize;
	Vec2 m_TextPos;
	wstring m_Text;
	float R;
	float G;
	float B;

public:
	GET_SET(float, FontSize);
	GET_SET(wstring, Text);

	virtual void SetScale(Vec2 _Scale) { m_FontSize = _Scale.x; }
	virtual void SetPos(Vec2 _Pos) { m_TextPos = _Pos; }

	virtual void Tick_UI() override;
	virtual void Render_UI(HDC _dc) override;

	virtual void BeginHover() override;
	virtual void Hover() override;
	virtual void EndHover() override;

	virtual void LBtnDown_UI() override;
	virtual void LBtnRelease_UI() override;
	virtual void LBtnClicked() override;

public:
	Text(wstring _text, Fonttype _fonttype, float _r, float _g, float _b);
	virtual ~Text();
};

