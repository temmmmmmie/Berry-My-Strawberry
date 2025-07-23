#include "pch.h"
#include "Gotcha.h"
#include "PanelUI.h"

#include "GameMgr.h"
#include "AssetMgr.h"

#include "BtnUI.h"
#include "ImageUI.h"
#include "Text.h"
#include "ATexture.h"
#include "ASound.h"
#include "VideoPlayer.h"

void Gotcha::BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider)
{
	m_Gotchapanel->SetPos(Vec2(960, 527.5f));
	GameMgr::GetInst()->Setpause(true);
}

void Gotcha::CloseGotchaPennel()
{
	m_Gotchapanel->SetPos(Vec2(-640, -560));
	GameMgr::GetInst()->Setpause(false);
}

void Gotcha::CloseGotchaBackPennel()
{
	m_Gotchabackground->SetPos(Vec2(-740, -560));
	m_GotchabackgroundBtn->m_Enabled = false;
	m_GotchaBtn->m_Enabled = true;
	VideoPlayer::GetInst()->Stop();
}

void Gotcha::StartGotcha()
{
	m_GotchaBtn->m_Enabled = false;
	float ran = GetRandomNum<float>(0, 100) ;
	float Acc = 0;
	for (size_t i = 0; i < m_Gotchalist.size(); i++)
	{
		Acc += m_Gotchalist[i].Percent;
		if (ran < Acc) {
			m_GotchaCharImg->SetTexture( m_Gotchalist[i].tex);
			m_GotchaCharImg->SetScale(Vec2(m_Gotchalist[i].tex->GetWidth(), m_Gotchalist[i].tex->GetHeight())* 0.4f);
			m_GotchaName->SetText(m_Gotchalist[i].Name);
			m_GotchaDesc->SetText(m_Gotchalist[i].Desc);
			if (m_Gotchalist[i].Star == 5) VideoPlayer::GetInst()->Play(L"5", false, false);
			else VideoPlayer::GetInst()->Play(L"4", false, false);
			break;
		}
	}

	m_Gotchabackground->SetPos(Vec2(960, 527.5f));
	DelayedTask task
	{
		1.3f,
		0.0f,
		[this]() { this->Display(); }
	};
	GameMgr::GetInst()->AddDelay(task);
}
void Gotcha::Display()
{
	m_GotchabackgroundBtn->m_Enabled = true;
}

void Gotcha::DisplayCrow()
{
	m_GotchabackgroundBtn->m_Enabled = true;
	AssetMgr::GetInst()->FindSound(L"BGM")->Stop();
	VideoPlayer::GetInst()->Play(L"MovingCrow", true,false);
}

Gotcha::Gotcha(ATexture* _tex, bool _hascollider, Vec2 _scale, Vec2 _offset, AnimationStruct* _animation)
	:Object::Object(_tex, _hascollider, _scale, _offset, _animation)
{
	vector< ATexture*> texs = {
		AssetMgr::GetInst()->LoadTexture(L"Jackdaw", L"Texture\\GotchaImg\\Jackdaw.png"),
		AssetMgr::GetInst()->LoadTexture(L"NormalAlbentio", L"Texture\\GotchaImg\\NormalAlbentio.png"),
		AssetMgr::GetInst()->LoadTexture(L"RealStrawberry", L"Texture\\GotchaImg\\RealStrawberry.png"),
		AssetMgr::GetInst()->LoadTexture(L"RealCrow", L"Texture\\GotchaImg\\RealCrow.png"),
		AssetMgr::GetInst()->LoadTexture(L"NormalMagpie", L"Texture\\GotchaImg\\NormalMagpie.png"),
		AssetMgr::GetInst()->LoadTexture(L"NormalCrow", L"Texture\\GotchaImg\\NormalCrow.png"),
	};
	for (size_t i = 0; i < m_Gotchalist.size(); i++)
	{
		if(texs.size() > i) m_Gotchalist[i].tex = texs[i];
	}
}

Gotcha::~Gotcha()
{
}
