#include "pch.h"
#include "Level_Start.h"
 
#include "ImageUI.h"
#include "AssetMgr.h"
#include "Camera.h"
#include "KeyMgr.h"
#include "GameMgr.h"
#include "ATexture.h"
#include "ASound.h"
#include "AVideo.h"
#include "VideoPlayer.h"
#include "Engine.h"

Level_Start::Level_Start()
	:LockClick(false)
{
}

Level_Start::~Level_Start()
{
}


void Level_Start::Begin()
{
	VideoPlayer::GetInst()->Play(L"MovingAlbentio", false, true);
	LockClick = false;
	Level::Begin();
}

void GonextLevel() {
	VideoPlayer::GetInst()->Stop();
	ChangeLevel(LEVEL_TYPE::TUTORIAL);
}

void Level_Start::Tick()
{
	if (KEY_TAP(KEY::ENTER))
	{
		AssetMgr::GetInst()->FindSound(L"BGM")->Stop();
		VideoPlayer::GetInst()->Stop();
		ChangeLevel(LEVEL_TYPE::FLIPBOOKEDIT);
	}
	if (KEY_TAP(KEY::LBTN) && !LockClick) {
		LockClick = true;
		Camera::GetInst()->AddCamEffect(FADE_OUT, 1, GonextLevel);
		Camera::GetInst()->AddCamEffect(FADE_IN, 0.7f);
	}
	Level::Tick();
}

void Level_Start::End()
{
	ClearAllActor();
}

