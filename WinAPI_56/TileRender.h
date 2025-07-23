#pragma once
#include "Component.h"

class ATexture;
class ASprite;

struct tTileInfo
{
    ASprite* Sprite;
    bool     bBlock;    
};


class TileRender :
    public Component
{
private:
    UINT                m_Col;
    UINT                m_Row;
    Vec2                m_TileSize; // 타일 1개의 크기   
    vector<tTileInfo>   m_vecTileInfo; // 모든 타일의 정보( m_Col * m_Row )

public:
    void SetColRow(UINT _Col, UINT _Row);
    UINT GetMaxCol() { return m_Col; }
    UINT GetMaxRow() { return m_Row; }

    GET_SET(Vec2, TileSize);
    void SetSprite(UINT _Col, UINT _Row, ASprite* _Sprite);

    void Save(const wstring& _FilePath);
    void Load(const wstring& _FilePath);

public:
    virtual void FinalTick() override;
    void Render(HDC _dc);

public:
    TileRender();
    virtual ~TileRender();
};

