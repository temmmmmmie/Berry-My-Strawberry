#include "pch.h"
#include "TileActor.h"

#include "TileRender.h"

TileActor::TileActor()
	: m_TileRender(nullptr)
{
	m_TileRender = AddComponent(new TileRender);
}

TileActor::~TileActor()
{
}

void TileActor::Tick()
{
}

void TileActor::Render(HDC _dc)
{
	m_TileRender->Render(_dc);
}