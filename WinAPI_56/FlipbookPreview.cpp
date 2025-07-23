#include "pch.h"
#include "FlipbookPreview.h"
#include "FlipbookPlayer.h"
#include "AFlipbook.h"
#include "ASprite.h"
#include "Level_FlipbookEditor.h"

void FlipbookPreview::SetFlip(AFlipbook* _flip)
{
	m_FlipbookPlayer->AddFlipbook(0, _flip);
	m_FlipbookPlayer->Play(0, 10.f, 0);

}

void FlipbookPreview::Begin()
{
}

void FlipbookPreview::Tick()
{
	if (!m_StopInfo)DisplayInfo();
}


void FlipbookPreview::Render(HDC _dc)
{
	if (Editorlevel->GetFlipEditorState() == FLIPPREVIEW) {
		m_FlipbookPlayer->Render(_dc);
	}
}

void FlipbookPreview::Play(int _fps, int _repeatcount)
{
	m_FlipbookPlayer->Play(0, _fps, _repeatcount);
	m_StopInfo = false;
}

void FlipbookPreview::Stop()
{
	m_FlipbookPlayer->Stop();
	m_StopInfo = true;
}

void FlipbookPreview::DisplayInfo()
{
	if (Editorlevel->GetFlipEditorState() == FLIPPREVIEW && m_Flipbook->GetMaxSprite() > 0) {
		Editorlevel->DisplayFPS(m_FlipbookPlayer->GetSpriteIdx());
		Editorlevel->DisplayOffset(m_Flipbook->GetSprite(m_FlipbookPlayer->GetSpriteIdx())->GetOffset());
	}
}

void FlipbookPreview::PrevFrame()
{
	int CurIdx = m_FlipbookPlayer->GetSpriteIdx();
	if (CurIdx == 0) {
		CurIdx = m_Flipbook->GetMaxSprite() - 1;
		m_FlipbookPlayer->SetSpriteIdx(CurIdx);
	}
	else
	{
		m_FlipbookPlayer->SetSpriteIdx(--CurIdx);
	}
	DisplayInfo();
	m_FlipbookPlayer->Play(0, 0, 0);
}

void FlipbookPreview::NextFrame()
{
	int CurIdx = m_FlipbookPlayer->GetSpriteIdx();
	if (CurIdx >= m_Flipbook->GetMaxSprite() - 1) {
		CurIdx = 0;
		m_FlipbookPlayer->SetSpriteIdx(0);
	}
	else
	{
		m_FlipbookPlayer->SetSpriteIdx(++CurIdx);
	}
	DisplayInfo();
	m_FlipbookPlayer->Play(0, 0, 0);
}

void FlipbookPreview::DeleteFrame()
{
	m_Flipbook->DeleteSprite(m_FlipbookPlayer->GetSpriteIdx());
	NextFrame();
	DisplayInfo();
}

void FlipbookPreview::SetOffset(Vec2 _offset)
{
	if (m_Flipbook->GetMaxSprite() != 0) {
		m_Flipbook->GetSprite(m_FlipbookPlayer->GetSpriteIdx())->SetOffset(_offset);

	}
}


FlipbookPreview::FlipbookPreview(Level_FlipbookEditor* _Curlevel, AFlipbook* _flip)
	:Editorlevel(_Curlevel)
{
	SetScale(Vec2(1, 1));
	m_FlipbookPlayer = AddComponent(new FlipbookPlayer);
	m_FlipbookPlayer->AddFlipbook(0, _flip);
	m_Flipbook = _flip;

}

FlipbookPreview::~FlipbookPreview()
{
}
