#include "pch.h"
#include "FlipbookPlayer.h"

#include "RenderMgr.h"
#include "ATexture.h"
#include "AFlipbook.h"
#include "ASprite.h"

#include "TimeMgr.h"
#include "Engine.h"


FlipbookPlayer::FlipbookPlayer()
	: Component(COMPONENT_TYPE::FLIPBOOKPLAYER)
	, m_CurFlipbook(nullptr)
	, m_SpriteIdx(0)
{
	SetName(L"FlipbookPlayer");
}

FlipbookPlayer::~FlipbookPlayer()
{
}

void FlipbookPlayer::FinalTick()
{
	if (nullptr == m_CurFlipbook)
		return;

	// 1회 재생 완료
	if (m_Finish)
	{
		if (m_Repeat)
		{
			m_SpriteIdx = 0;
			m_Finish = false;
			m_AccTime = 0.f;
		}
		else
		{
			--m_PlayCount;
			if (0 < m_PlayCount)
			{
				m_SpriteIdx = 0;
				m_Finish = false;
				m_AccTime = 0.f;
			}
		}		
	}


	float Limit = 1.f / m_FPS;

	m_AccTime += DT;

	if (Limit <= m_AccTime)
	{
		++m_SpriteIdx;
		m_AccTime -= Limit;

		if (m_CurFlipbook->GetMaxSprite() <= m_SpriteIdx)
		{
			m_SpriteIdx -= 1;
			m_Finish = true;
			if(m_OnAnimationFinished)	m_OnAnimationFinished();
		}		
	}
}
void FlipbookPlayer::Render(HDC _dc)
{
	if (nullptr == m_CurFlipbook)
		return;

	// 컴포넌트 소유자(Actor) 의 위치
	Vec2 vPos = GetOwner()->GetRenderPos();
	Vec2 vScale = GetOwner()->GetScale();

	if (m_SpriteIdx >= m_CurFlipbook->GetMaxSprite()) return;
	ASprite* pSprite = m_CurFlipbook->GetSprite(m_SpriteIdx);

	Vec2 vOffset = pSprite->GetOffset();
	RenderMgr::GetInst()->Draw(pSprite->GetAtlas(), Vec2(vPos.x + vOffset.x, vPos.y + vOffset.y), vScale, pSprite->GetLeftTop(), pSprite->GetSlice());
}

void FlipbookPlayer::AddFlipbook(int _Idx, AFlipbook* _Flipbook)
{
	if (m_PlayList.size() <= _Idx)
	{
		m_PlayList.resize(_Idx + 1);
	}

	m_PlayList[_Idx] = _Flipbook;
}