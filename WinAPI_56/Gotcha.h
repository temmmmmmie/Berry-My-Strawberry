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
		{nullptr, L"갈가마귀", L"삭제해라", 5, 0.1f},
		{nullptr, L"알벤티오", L"이 게임의 주인공!", 5, 10},
		{nullptr, L"진짜 딸기", L"완전 딸기", 4, 15},
		{nullptr, L"진짜 까마귀", L"완전 까마귀", 4, 15},
		{nullptr, L"리버스 까치", L"깍깍깍깍깍", 4, 20},
		{nullptr, L"평범한 까마귀", L"까악까악", 4, 40},
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

