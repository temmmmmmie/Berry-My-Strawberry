#include "pch.h"
#include "SpriteActor.h"

#include "SpriteRender.h"

void SpriteActor::Tick()
{
}

void SpriteActor::Render(HDC _dc)
{
	m_SpriteRender->Render(_dc);
}

SpriteActor::SpriteActor(Level_FlipbookEditor* _Curlevel)
	:m_SpriteRender(nullptr)
{
	m_SpriteRender = AddComponent(new SpriteRender(_Curlevel));
}
SpriteActor::~SpriteActor()
{
}
