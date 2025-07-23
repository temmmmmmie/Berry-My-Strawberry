#include "pch.h"
#include "Level_Tutorial.h"

#include "Camera.h"
#include "AssetMgr.h"
#include "GameMgr.h"
#include "KeyMgr.h"
#include "Engine.h"

#include "ImageUI.h"

void Level_Tutorial::Begin()
{
	ATexture* Backtex = AssetMgr::GetInst()->LoadTexture(L"Tutorial", L"Texture\\Tutorial.png");
	ImageUI* pBackground = new ImageUI;
	pBackground->SetName(L"Tutorial");
	pBackground->SetTexture(Backtex);
	pBackground->SetUIMode(UI_MODE::SCREEN);
	pBackground->SetScale(Vec2(1920, 1055));
	pBackground->SetPos(Vec2(960, 527.5f));

	AddActor(ACTOR_TYPE::UI, pBackground);
	LockClick = false;
	Level::Begin();
}
void GostageLevel() {

	GameMgr::GetInst()->init();
	ChangeLevel(LEVEL_TYPE::STAGE_01);
}
void Level_Tutorial::Tick()
{
	if (KEY_TAP(KEY::LBTN) && !LockClick) {
		LockClick = true;
		Camera::GetInst()->AddCamEffect(FADE_OUT, 1, GostageLevel);
		Camera::GetInst()->AddCamEffect(FADE_IN, 0.7f);
	}
	Level::Tick();
}

void Level_Tutorial::End()
{
	ClearAllActor();
}

Level_Tutorial::Level_Tutorial()
	:LockClick(false)
{
}

Level_Tutorial::~Level_Tutorial()
{
}
