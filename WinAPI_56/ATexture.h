#pragma once
#include "Asset.h"
#include <GL/gl.h>

class ATexture :
    public Asset
{
private:
    GLuint     m_hBitmap;
    int m_Width;
    int m_Height;

public:
    GLuint& GetLuint() { return m_hBitmap; }
    int GetWidth() { return m_Width; }
    int GetHeight() { return m_Height; }
private:
    ATexture();
    virtual ~ATexture();
    friend class AssetMgr;

    virtual int Load(const wstring& _FilePath) override;


};

