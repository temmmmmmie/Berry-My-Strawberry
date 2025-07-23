#include "pch.h"
#include "AFlipbook.h"


AFlipbook::AFlipbook()
{
}

AFlipbook::~AFlipbook()
{
}

void AFlipbook::DeleteSprite(int _Idx)
{
	vector<ASprite*>::iterator iter = m_vecSprite.begin();
	for (size_t i = 0; i < _Idx; i++)iter++;
	m_vecSprite.erase(iter);
}

void AFlipbook::AddSprite(int Idx, ASprite* _Sprite)
{
	if (m_vecSprite.size() <= Idx)
	{
		m_vecSprite.resize(Idx + 1);
	}	

	m_vecSprite[Idx] = _Sprite;
}

void AFlipbook::ResizeVec(int Size)
{
	if (m_vecSprite.size() < Size)
	{
		m_vecSprite.resize(Size);
	}

	else if (m_vecSprite.size() > Size)
	{
		vector<ASprite*> vecTemp;
		vecTemp.resize(Size);
		vecTemp.swap(m_vecSprite);
	}
}

int AFlipbook::Save(const wstring& _FilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _FilePath.c_str(), L"wb");

	SaveFlipbookRef(this, pFile);

	UINT SpriteCount = (UINT)m_vecSprite.size();
	fwrite(&SpriteCount, sizeof(UINT), 1, pFile);

	for (size_t i = 0; i < m_vecSprite.size(); ++i)
	{
		SaveSpriteRef(m_vecSprite[i], pFile);
	}


	fclose(pFile);

	return S_OK;
}

int AFlipbook::Load(const wstring& _FilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _FilePath.c_str(), L"rb");

	LoadFlipbookRef(pFile, this);

	UINT SpriteCount = 0;
	fread(&SpriteCount, sizeof(UINT), 1, pFile);

	if(m_vecSprite.size() != 0) m_vecSprite.clear();
	for (size_t i = 0; i < SpriteCount; ++i)
	{
		ASprite* pSprite = LoadSpriteRef(pFile);
		m_vecSprite.push_back(pSprite);
	}
	fclose(pFile);

	return S_OK;
}
