#include "pch.h"
#include "ASprite.h"
#include "AssetMgr.h"
#include "ATexture.h"

ASprite::ASprite()
	: m_AtlasTex(nullptr)
{
}

ASprite::~ASprite()
{
}

void ASprite::Create(ATexture* _AtlasTex, Vec2 _LeftTop, Vec2 _Slice)
{
	m_AtlasTex = _AtlasTex;
	m_LeftTop = _LeftTop;
	m_Slice = _Slice;
}

int ASprite::Save(const wstring& _FilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _FilePath.c_str(), L"wb");

	fwrite(&m_LeftTop, sizeof(Vec2), 1, pFile);
	fwrite(&m_Slice, sizeof(Vec2), 1, pFile);
	fwrite(&m_Offset, sizeof(Vec2), 1, pFile);

	// ����Ű�� �ִ� Texture �� �־����� �����Ѵ�.
	bool Exist = m_AtlasTex;
	fwrite(&Exist, sizeof(bool), 1, pFile);

	if (Exist)
	{
		// Ÿ���� ����Ű�� �ִ� Sprite �� Key ���ڿ��� ���Ͽ� �����Ѵ�.
		wstring Key = m_AtlasTex->GetKey();
		wstring Path = m_AtlasTex->GetRelativePath();
		SaveWString(Key, pFile);
		SaveWString(Path, pFile);
	}

	fclose(pFile);

	return 0;
}

int ASprite::Load(const wstring& _FilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _FilePath.c_str(), L"rb");

	fread(&m_LeftTop, sizeof(Vec2), 1, pFile);
	fread(&m_Slice, sizeof(Vec2), 1, pFile);
	fread(&m_Offset, sizeof(Vec2), 1, pFile);

	// ����Ű�� �ִ� Texture �� �־����� �����Ѵ�.
	bool Exist = false;
	fread(&Exist, sizeof(bool), 1, pFile);

	if (Exist)
	{
		// Ÿ���� ����Ű�� �ִ� Sprite �� Key ���ڿ��� ���Ͽ� �����Ѵ�.
		wstring Key, Path;
		LoadWString(Key, pFile);
		LoadWString(Path, pFile);
		m_AtlasTex = AssetMgr::GetInst()->LoadTexture(Key, Path);
	}

	fclose(pFile);

	return 0;
}