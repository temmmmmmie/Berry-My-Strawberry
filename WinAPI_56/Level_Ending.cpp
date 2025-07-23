#include "pch.h"
#include "Level_Ending.h"

#include "ImageUI.h"
#include "AssetMgr.h"
#include "GameMgr.h"
#include "Camera.h"
#include "KeyMgr.h"
#include "ATexture.h"
#include "Engine.h"

void Level_Ending::Begin()
{
	ATexture* Backtex = nullptr;
	if (GameMgr::GetInst()->GetStrawberry() >= GameMgr::GetInst()->GetStrawberryGoal())
		Backtex = AssetMgr::GetInst()->LoadTexture(L"Ending", L"Texture\\Success.png");
	else
		Backtex = AssetMgr::GetInst()->LoadTexture(L"Ending", L"Texture\\Fail.png");

	ImageUI* pBackground = new ImageUI;
	pBackground->SetName(L"Ending");
	pBackground->SetTexture(Backtex);
	pBackground->SetUIMode(UI_MODE::SCREEN);
	pBackground->SetScale(Vec2(1920, 1055));
	pBackground->SetPos(Vec2(960, 527.5f));

	AddActor(ACTOR_TYPE::UI, pBackground);

	LockClick = false;
	Level::Begin();
}
void GoTitleLevel() {
	GameMgr::GetInst()->init();
	ChangeLevel(LEVEL_TYPE::START);
}
void Level_Ending::Tick()
{
	if (KEY_TAP(KEY::LBTN) && !LockClick) {
		LockClick = true;
		Camera::GetInst()->AddCamEffect(FADE_OUT, 1, GoTitleLevel);
		Camera::GetInst()->AddCamEffect(FADE_IN, 0.7f);
	}
	Level::Tick();
}

void Level_Ending::End()
{
	ClearAllActor();
}

Level_Ending::Level_Ending()
	:LockClick(false)
{
}

Level_Ending::~Level_Ending()
{
}
