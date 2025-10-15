#include "pch.h"

#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "Collider.h"
#include "RigidBody.h"
#include "FlipbookPlayer.h"
#include "StateMachine.h"
#include "AssetMgr.h"
#include "GameMgr.h"
#include "Engine.h"

#include "Player.h"
#include "Rabbit.h"
#include "Wagon.h"
#include "Strawberrry.h"
#include "Object.h"
#include "Tool.h"
#include "Gotcha.h"
#include "Cloud.h"
#include "Text.h"
#include "PanelUI.h"
#include "BtnUI.h"
#include "ImageUI.h"
#include "Level_Stage01.h"
#include "Camera.h"

void Level_Stage01::Begin()
{
	Camera::GetInst()->SetLook(Vec2(0,0) );
	GameMgr::GetInst()->SetLevel(this);
	// 충돌 설정
	CollisionMgr::GetInst()->CollisionCheckClear();
	CollisionMgr::GetInst()->CollisionCheck(PLAYER, OBJECT, true);
	CollisionMgr::GetInst()->CollisionCheck(PLAYER, INTERACTABLE, true);
	CollisionMgr::GetInst()->CollisionCheck(PLAYER_PROJECTILE, INTERACTABLE, true);
	CollisionMgr::GetInst()->CollisionCheck(PLAYER_PROJECTILE, STRAWBERRY, true);
	CollisionMgr::GetInst()->CollisionCheck(PLAYER_PROJECTILE, ENERMY, true);
	CollisionMgr::GetInst()->CollisionCheck(STRAWBERRY, ENERMY, true);
	{
		ATexture* tex2 = AssetMgr::GetInst()->LoadTexture(L"sky", L"Texture\\sky.png");
		Actor* pSkyActor = new Object(tex2, false);
		pSkyActor->SetName(L"sky");
		pSkyActor->SetPos(Vec2(0, -10));
		pSkyActor->SetScale(Vec2(1, 1));
		AddActor(BACKGROUND, pSkyActor);

		ATexture* tex3 = AssetMgr::GetInst()->LoadTexture(L"cloud", L"Texture\\cloud.png");
		AnimationStruct ani = {
			Animationtype::MOVE_RIGHT,
			5,
			true
		};
		Actor* pCloudActor = new Cloud(tex3, false, Vec2(0,0), Vec2(0,0), &ani);
		pCloudActor->SetName(L"cloud");
		pCloudActor->SetPos(Vec2(-800, -350));
		pCloudActor->SetScale(Vec2(1, 1));
		AddActor(BACKGROUND, pCloudActor);

		ATexture* tex1 = AssetMgr::GetInst()->LoadTexture(L"ground", L"Texture\\ground.png");
		Actor* pGroundActor = new Object(tex1, false);
		pGroundActor->SetName(L"Ground");
		pGroundActor->SetPos(Vec2(0, 30));
		pGroundActor->SetScale(Vec2(1, 1));
		AddActor(BACKGROUND, pGroundActor);
	}
	// Start 레벨 초기 액터들 생성
	Actor* pActor = new Player;
	pActor->SetName(L"Player");
	pActor->SetPos(Vec2(0, 0));
	pActor->SetScale(Vec2(1, 1));
	AddActor(PLAYER, pActor);

	ATexture* tex4 = AssetMgr::GetInst()->LoadTexture(L"tableLeft", L"Texture\\tableLeft.png");
	Actor* pTableActor1 = new Object(tex4, true, Vec2(280, 120), Vec2(-20, -50));
	pTableActor1->SetName(L"Table1");
	pTableActor1->SetPos(Vec2(-450, 180));
	pTableActor1->SetScale(Vec2(1, 1));
	AddActor(OBJECT, pTableActor1);

	ATexture* tex5 = AssetMgr::GetInst()->LoadTexture(L"tableRight", L"Texture\\tableRight.png");
	Actor* pTableActor2 = new Object(tex5, true, Vec2(280, 120), Vec2(-20, -50));
	pTableActor2->SetName(L"Table2");
	pTableActor2->SetPos(Vec2(200, 180));
	pTableActor2->SetScale(Vec2(1, 1));
	AddActor(OBJECT, pTableActor2);


	{
		ATexture* tex6 = AssetMgr::GetInst()->LoadTexture(L"sign1", L"Texture\\sign1.png");
		Actor* pSignActor = new Object(tex6, false);
		pSignActor->SetName(L"sign1");
		pSignActor->SetPos(Vec2(-640, -210));
		pSignActor->SetScale(Vec2(1, 1));
		AddActor(BACKGROUND, pSignActor);

		ATexture* tex7 = AssetMgr::GetInst()->LoadTexture(L"sign2", L"Texture\\sign2.png");
		Actor* pSignActor1 = new Object(tex7, false);
		pSignActor1->SetName(L"sign2");
		pSignActor1->SetPos(Vec2(-440, -210));
		pSignActor1->SetScale(Vec2(1, 1));
		AddActor(BACKGROUND, pSignActor1);

		ATexture* tex8 = AssetMgr::GetInst()->LoadTexture(L"sign3", L"Texture\\sign3.png");
		Actor* pSignActor2 = new Object(tex8, false);
		pSignActor2->SetName(L"sign3");
		pSignActor2->SetPos(Vec2(400, -210));
		pSignActor2->SetScale(Vec2(1, 1));
		AddActor(BACKGROUND, pSignActor2);

		ATexture* tex9 = AssetMgr::GetInst()->LoadTexture(L"sign4", L"Texture\\sign4.png");
		Actor* pSignActor3 = new Object(tex9, false);
		pSignActor3->SetName(L"sign4");
		pSignActor3->SetPos(Vec2(600, -210));
		pSignActor3->SetScale(Vec2(1, 1));
		AddActor(BACKGROUND, pSignActor3);
	}
	Actor* pWagon = new Wagon;
	pWagon->SetName(L"Wagon");
	pWagon->SetPos(Vec2(800, 160));
	pWagon->SetScale(Vec2(1, 1));
	AddActor(INTERACTABLE, pWagon);

	Actor* pToolSword = new Tool(tooltype::SWORD);
	pToolSword->SetName(L"Sword");
	pToolSword->SetPos(Vec2(110, 110));
	pToolSword->SetScale(Vec2(1, 1));
	AddActor(INTERACTABLE, pToolSword);

	Actor* pToolPotion = new Tool(tooltype::POTION);
	pToolPotion->SetName(L"Potion");
	pToolPotion->SetPos(Vec2(230, 110));
	pToolPotion->SetScale(Vec2(1, 1));
	AddActor(INTERACTABLE, pToolPotion);

	Actor* pToolSeed = new Tool(tooltype::SEED);
	pToolSeed->SetName(L"Seed");
	pToolSeed->SetPos(Vec2(-540, 120));
	pToolSeed->SetScale(Vec2(1, 1));
	AddActor(INTERACTABLE, pToolSeed);

	Actor* pToolWater = new Tool(tooltype::WATER);
	pToolWater->SetName(L"Water");
	pToolWater->SetPos(Vec2(-420, 110));
	pToolWater->SetScale(Vec2(1, 1));
	AddActor(INTERACTABLE, pToolWater);
	{
		Actor* pStrawberry0 = new Strawberrry;
		pStrawberry0->SetName(L"Strawberry0");
		pStrawberry0->SetPos(Vec2(-250, -210));
		pStrawberry0->SetScale(Vec2(1, 1));
		AddActor(STRAWBERRY, pStrawberry0);

		Actor* pStrawberry1 = new Strawberrry;
		pStrawberry1->SetName(L"Strawberry1");
		pStrawberry1->SetPos(Vec2(-130, -210));
		pStrawberry1->SetScale(Vec2(1, 1));
		AddActor(STRAWBERRY, pStrawberry1);

		Actor* pStrawberry2 = new Strawberrry;
		pStrawberry2->SetName(L"Strawberry2");
		pStrawberry2->SetPos(Vec2(-10, -210));
		pStrawberry2->SetScale(Vec2(1, 1));
		AddActor(STRAWBERRY, pStrawberry2);

		Actor* pStrawberry3 = new Strawberrry;
		pStrawberry3->SetName(L"Strawberry3");
		pStrawberry3->SetPos(Vec2(120, -210));
		pStrawberry3->SetScale(Vec2(1, 1));
		AddActor(STRAWBERRY, pStrawberry3);

		Actor* pStrawberry4 = new Strawberrry;
		pStrawberry4->SetName(L"Strawberry4");
		pStrawberry4->SetPos(Vec2(230, -210));
		pStrawberry4->SetScale(Vec2(1, 1));
		AddActor(STRAWBERRY, pStrawberry4);
	}

	ATexture* tex18 = AssetMgr::GetInst()->LoadTexture(L"Ui", L"Texture\\UI.png");
	ImageUI* pUi = new ImageUI();
	pUi->SetName(L"Ui");
	pUi->SetTexture(tex18);
	pUi->SetUIMode(SCREEN);
	pUi->SetScale(Vec2(144 * 1.5f, 109 * 1.5f));
	pUi->SetPos(Vec2(150, 130));
	AddActor(UI, pUi);

	Text* pText = new Text(L"0", Fonttype::HeirofLightBold, 0.1f, 0.1f, 0.1f);
	GameMgr::GetInst()->SetScoreText(pText);
	pText->SetName(L"Score");
	pText->SetUIMode(SCREEN);
	pText->SetScale(Vec2(0.7f, 0.7f));
	pText->SetPos(Vec2(56 + 30, 95 + 50));
	AddActor(UI, pText);
	
	Text* pText2 = new Text(L"0", Fonttype::HeirofLightBold, 0.1f, 0.1f, 0.1f);
	GameMgr::GetInst()->SetTimerText(pText2);
	pText2->SetName(L"Timer");
	pText2->SetUIMode(SCREEN);
	pText2->SetScale(Vec2(0.7f, 0.7f));
	pText2->SetPos(Vec2(50 + 25, 41 + 30));
	AddActor(UI, pText2);



	ATexture* tex11 = AssetMgr::GetInst()->LoadTexture(L"GotchaPannel", L"Texture\\GotchaPannel.png");
	PanelUI* pPanel = new PanelUI(tex11);
	pPanel->SetName(L"Panel 1");
	pPanel->SetUIMode(UI_MODE::SCREEN);
	pPanel->SetScale(Vec2(0.5f, 0.5f));
	pPanel->SetPos(Vec2(-640, -560));
	
	
	//========================================<<GotchaWindow>>===============================================
	
	ATexture* tex14 = AssetMgr::GetInst()->LoadTexture(L"GotchaBackground", L"Texture\\GotchaBackground.png");
	PanelUI* pPanel2 = new PanelUI(tex14);
	pPanel2->SetName(L"Panel 2");
	pPanel2->SetUIMode(UI_MODE::SCREEN);
	pPanel2->SetScale(Vec2(1, 1));
	pPanel2->SetPos(Vec2(-740, -560));

	ImageUI* pGotchacharImg = new ImageUI;
	pGotchacharImg->SetName(L"GotchaCharImg");
	pGotchacharImg->SetTexture(nullptr);
	pGotchacharImg->SetUIMode(UI_MODE::SCREEN);
	pGotchacharImg->SetScale(Vec2(1000, 1300));
	pGotchacharImg->SetPos(Vec2(-230, 0));
	pPanel2->AddChildUI(pGotchacharImg);

	Text* pText3 = new Text(L"이름", Fonttype::HeirofLightBold, 1, 1, 1);
	pText3->SetName(L"GotchaCharName");
	pText3->SetUIMode(SCREEN);
	pText3->SetScale(Vec2(1, 1));
	pText3->SetPos(Vec2(100, -150));
	pPanel2->AddChildUI(pText3);
	
	Text* pText4 = new Text(L"설명", Fonttype::HeirofLightRegular, 1, 1, 1);
	pText4->SetName(L"GotchaCharDesc");
	pText4->SetUIMode(SCREEN);
	pText4->SetScale(Vec2(0.7f, 0.7f));
	pText4->SetPos(Vec2(100, -65));
	pPanel2->AddChildUI(pText4);

	//=================================================================================================
	
	
	ATexture* tex10 = AssetMgr::GetInst()->LoadTexture(L"Gotcha", L"Texture\\Gotcha.png");
	Gotcha* pGotcha = new Gotcha(tex10, true, Vec2(80, 70), Vec2(0, 0));
	pGotcha->SetName(L"Gotcha");
	pGotcha->SetPos(Vec2(900, 300));
	pGotcha->SetScale(Vec2(1, 1));
	AddActor(INTERACTABLE, pGotcha);

	ATexture* tex12 = AssetMgr::GetInst()->LoadTexture(L"Close", L"Texture\\Close.png");
	BtnUI* pBtnUI = new BtnUI(tex12);
	pBtnUI->SetName(L"GotchaClosebtn");
	pBtnUI->SetDelegate(pGotcha, (MEM_FUNC)&Gotcha::CloseGotchaPennel);
	pBtnUI->SetUIMode(SCREEN);
	pBtnUI->SetScale(Vec2(50.f, 50.f));
	pBtnUI->SetPos(Vec2(400.f, -250.f));
	pPanel->AddChildUI(pBtnUI);

	ATexture* tex13 = AssetMgr::GetInst()->LoadTexture(L"StartGotcha", L"Texture\\StartGotcha.png");
	BtnUI* pBtnUI2 = new BtnUI(tex13);
	pBtnUI2->SetName(L"StartGotcha");
	pBtnUI2->SetDelegate(pGotcha, (MEM_FUNC)&Gotcha::StartGotcha);
	pBtnUI2->SetUIMode(SCREEN);
	pBtnUI2->SetScale(Vec2(110.f, 50.f));
	pBtnUI2->SetPos(Vec2(300.f, 150.f));
	pPanel->AddChildUI(pBtnUI2);

	BtnUI* pBtnUI3 = new BtnUI();
	pBtnUI3->SetName(L"GotchaBackgroundClosebtn");
	pBtnUI3->SetDelegate(pGotcha, (MEM_FUNC)&Gotcha::CloseGotchaBackPennel);
	pBtnUI3->SetUIMode(SCREEN);
	pBtnUI3->SetScale(Vec2(1500.f, 1000.f));
	pBtnUI3->SetPos(Vec2(-750, -540));
	pBtnUI3->m_Enabled = false;
	pPanel2->AddChildUI(pBtnUI3);

	AddActor(UI, pPanel);
	AddActor(UI, pPanel2);

	pGotcha->m_Gotchapanel = pPanel;
	pGotcha->m_GotchaBtn = pBtnUI2;
	pGotcha->m_Gotchabackground = pPanel2;
	pGotcha->m_GotchabackgroundBtn = pBtnUI3;
	pGotcha->m_GotchaCharImg = pGotchacharImg;
	pGotcha->m_GotchaName = pText3;
	pGotcha->m_GotchaDesc = pText4;
	// 레벨안에 있는 Actor 들에게 Begin 을 호출해준다.
	Level::Begin();
}

void Level_Stage01::Tick()
{
	Level::Tick();
}

void Level_Stage01::End()
{
	ClearAllActor();
}

void Level_Stage01::ClearActor(ACTOR_TYPE _type)
{
	Level::ClearActor(_type);
}

void Level_Stage01::SpawnRabbit(int _num)
{
	Vec2 Randompos = Vec2(0, 0);
	float rad = 1500;
	Vec2 center = Vec2(0, 0);

	for (size_t i = 0; i < _num; i++)
	{
		switch (GetRandomNum<int>(0, 2))
		{
		case 0:
			Randompos = Vec2(center.x - rad / 2, GetRandomNum<float>(center.y - rad / 8, center.y + rad / 2));
			break;
		case 1:
			Randompos = Vec2(GetRandomNum<float>(center.x - rad / 2, center.x + rad / 2), center.y + rad / 2);
			break;
		case 2:
			Randompos = Vec2(center.x + rad / 2, GetRandomNum<float>(center.y - rad / 8, center.y + rad / 2));
			break;
		}

		Rabbit* pRabbit = new Rabbit;
		pRabbit->SetName(L"Rabbit");
		pRabbit->SetPos(Randompos);
		pRabbit->Settarget();
		pRabbit->SetScale(Vec2(1, 1));
		AddActor(ENERMY, pRabbit);
	}

}

Level_Stage01::Level_Stage01()
{
}

Level_Stage01::~Level_Stage01()
{
}
