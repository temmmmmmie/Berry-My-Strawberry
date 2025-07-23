#pragma once
#include "Asset.h"


class ATexture;

// 특정 텍스쳐의 일부분을 나타내는 에셋
class ASprite :
    public Asset
{
private:
    ATexture*   m_AtlasTex;
    Vec2        m_LeftTop;
    Vec2        m_Slice;
    Vec2        m_Offset;

public:
    ATexture* GetAtlas() { return m_AtlasTex; }
    void SetAltas(ATexture* _Tex) { m_AtlasTex = _Tex; }
    GET_SET(Vec2, LeftTop);
    GET_SET(Vec2, Slice);
    GET_SET(Vec2, Offset);

public:
    void Create(ATexture* _AtlasTex, Vec2 _LeftTop, Vec2 _Slice);
    int Save(const wstring& _FilePath);
    int Load(const wstring& _FilePath);

public:
    ASprite();
    virtual ~ASprite();
};

