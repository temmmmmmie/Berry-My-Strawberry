#pragma once


class UIMgr
{
	SINGLE(UIMgr);
private:
	class Widget* m_FocusedUI;
	bool		  m_bFocuedChange;


public:
	void Tick();

private:
	class Widget* GetPriorityUI(Widget* _Parent);

};

