#pragma once
#include "Asset.h"

class ASprite;

class AFlipbook :
    public Asset
{
private:
    vector<ASprite*>    m_vecSprite;

public:
    int GetMaxSprite() { return m_vecSprite.size(); }
    ASprite* GetSprite(int _Idx) { return m_vecSprite[_Idx]; }
    void DeleteSprite(int _Idx);

public:
    void AddSprite(int Idx, ASprite* _Sprite);
    void ResizeVec(int Size);
    
    int Save(const wstring& _FilePath);
    int Load(const wstring& _FilePath);

public:
    AFlipbook();
    virtual ~AFlipbook();
};

