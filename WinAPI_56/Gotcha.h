#pragma once
#include <Object.h>

struct tGotchaData
{
	ATexture* tex;
	wstring Name;
	wstring Desc;
	int Star;
	float Percent;
};
class PanelUI;
class BtnUI;
class ImageUI;
class Text;
class Gotcha :
	public Object
{
private:

	vector <tGotchaData> m_Gotchalist = {
		{nullptr, L"��������", L"�����ض�", 5, 0.1f},
		{nullptr, L"�˺�Ƽ��", L"�� ������ ���ΰ�!", 5, 10},
		{nullptr, L"��¥ ����", L"���� ����", 4, 15},
		{nullptr, L"��¥ ���", L"���� ���", 4, 15},
		{nullptr, L"������ ��ġ", L"������", 4, 20},
		{nullptr, L"����� ���", L"��Ǳ��", 4, 40},
	};
	
public:
	PanelUI* m_Gotchapanel;
	BtnUI* m_GotchaBtn;
	PanelUI* m_Gotchabackground;
	BtnUI* m_GotchabackgroundBtn;

	ImageUI* m_GotchaCharImg;
	Text* m_GotchaName;
	Text* m_GotchaDesc;

	virtual void BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
	void CloseGotchaPennel();
	void CloseGotchaBackPennel();
	void StartGotcha();

	void Display();
	void DisplayCrow();


	Gotcha(ATexture* _tex, bool _hascollider, Vec2 _scale = Vec2(0, 0), Vec2 _offset = Vec2(0, 0), AnimationStruct* _animation = nullptr);
	~Gotcha();
};

