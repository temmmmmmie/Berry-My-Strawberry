#include "pch.h"
#include "TileRender.h"

#include "Actor.h"

#include "AssetMgr.h"
#include "ASprite.h"
#include "RenderMgr.h"
#include "ATexture.h"

TileRender::TileRender()
	: Component(COMPONENT_TYPE::TILERENDER)
	, m_Col(1)
	, m_Row(1)
	, m_TileSize(Vec2(64.f, 64.f))
{

}

TileRender::~TileRender()
{

}

void TileRender::FinalTick()
{
	Vec2 vPos = GetOwner()->GetRenderPos();

	// DebugRender
	for (UINT i = 0; i < m_Row + 1; ++i)
	{
		Vec2 vStart = vPos + Vec2(0.f, (float)i * m_TileSize.y);
		Vec2 vEnd = vStart + Vec2(m_TileSize.x * (float)m_Col, 0.f);
		DrawDebugLine(vStart, vEnd, PEN_TYPE::GREEN, 0.f);
	}

	for (UINT i = 0; i < m_Col + 1; ++i)
	{
		Vec2 vStart = vPos + Vec2((float)i * m_TileSize.x, 0.f);
		Vec2 vEnd = vStart + Vec2(0.f, m_TileSize.y * (float)m_Row);
		DrawDebugLine(vStart, vEnd, PEN_TYPE::GREEN, 0.f);
	}
}

void TileRender::Render(HDC _dc)
{
	Vec2 vActorPos = GetOwner()->GetRenderPos();

	for (int i = 0; i < m_vecTileInfo.size(); ++i)
	{
		if (nullptr == m_vecTileInfo[i].Sprite)
			continue;

		int Row = i / m_Col;
		int Col = i % m_Col;

		Vec2 vTilePos = vActorPos + Vec2((float)Col * m_TileSize.x, (float)Row * m_TileSize.y);

		RenderMgr::GetInst()->
			Draw(m_vecTileInfo[i].Sprite->GetAtlas(),
				Vec2((int)vTilePos.x + 32, (int)vTilePos.y + 32),
				Vec2(1, 1),
				Vec2((int)m_vecTileInfo[i].Sprite->GetLeftTop().x, (int)m_vecTileInfo[i].Sprite->GetLeftTop().y),
				Vec2((int)m_vecTileInfo[i].Sprite->GetSlice().x, (int)m_vecTileInfo[i].Sprite->GetSlice().y)
				);
	}
}

void TileRender::SetColRow(UINT _Col, UINT _Row)
{
	m_Col = _Col;
	m_Row = _Row;

	if (m_vecTileInfo.size() < m_Col * m_Row)
	{		
		m_vecTileInfo.resize(m_Col * m_Row);
	}

	else if (m_vecTileInfo.size() > m_Col * m_Row)
	{
		vector<tTileInfo> vecTemp;
		vecTemp.resize(m_Col * m_Row);
		vecTemp.swap(m_vecTileInfo);
	}
}

void TileRender::SetSprite(UINT _Col, UINT _Row, ASprite* _Sprite)
{
	int Idx = _Row * m_Col + _Col;

	m_vecTileInfo[Idx].Sprite = _Sprite;
}

void TileRender::Save(const wstring& _FilePath)
{
	// 파일 입출력
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _FilePath.c_str(), L"wb");

	fwrite(&m_Col, sizeof(UINT), 1, pFile);
	fwrite(&m_Row, sizeof(UINT), 1, pFile);
	fwrite(&m_TileSize, sizeof(Vec2), 1, pFile);

	for (size_t i = 0; i < m_vecTileInfo.size(); ++i)
	{
		fwrite(&m_vecTileInfo[i].bBlock, sizeof(bool), 1, pFile);
		SaveSpriteRef(m_vecTileInfo[i].Sprite, pFile);
	}

	fclose(pFile);
}

void TileRender::Load(const wstring& _FilePath)
{
	// 파일 입출력
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _FilePath.c_str(), L"rb");

	UINT Col = 0;
	UINT Row = 0;
	fread(&Col, sizeof(UINT), 1, pFile);
	fread(&Row, sizeof(UINT), 1, pFile);
	SetColRow(Col, Row);

	fread(&m_TileSize, sizeof(Vec2), 1, pFile);

	for (size_t i = 0; i < m_vecTileInfo.size(); ++i)
	{
		fread(&m_vecTileInfo[i].bBlock, sizeof(bool), 1, pFile);

		m_vecTileInfo[i].Sprite = LoadSpriteRef(pFile);
	}

	fclose(pFile);
}