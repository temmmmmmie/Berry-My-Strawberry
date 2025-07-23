#pragma once
#include "Component.h"

class ATexture;
class ASprite;
class AFlipbook;
class Level_FlipbookEditor;

class SpriteRender:
	public Component
{
private:
    Level_FlipbookEditor* m_Level;

    AFlipbook*          m_Curflip;
    ATexture*           m_Curtex;

    Vec2                m_texresolution;

public:
    ATexture* GetTex() { return m_Curtex; }
    AFlipbook* GetFlip(){ return m_Curflip; }
    Vec2 GetTexResolution() { return m_texresolution; }
    
    void SetColRow(UINT _Col, UINT _Row);
    void AddSprite(Vec2 _Lefttop, Vec2 _Slice);
    void NewFlip(const wstring& _FilePath);
    void ClearFlip();

    void Save(const wstring& _FilePath, const wstring& _Filename);
    void Load(const wstring& _FilePath);

public:
    virtual void FinalTick() override;
    void Render(HDC _dc);

public:
    SpriteRender(Level_FlipbookEditor* _Curlevel);
    ~SpriteRender();
};

