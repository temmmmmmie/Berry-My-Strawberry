#include "pch.h"
#include "Text.h"

#include "ShaderLoader.h"
#include "Engine.h"

Text::Text(wstring _text, Fonttype _fonttype, float _r, float _g, float _b)
	:m_Fonttype(_fonttype),
	m_Text(_text),
    R(_r),
    G(_g),
    B(_b)
{


}
Text::~Text() {}

void Text::Tick_UI()
{

}

void Text::Render_UI(HDC _dc)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(R, G, B, 1.0f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Engine::GetInst()->GetResolution().x, Engine::GetInst()->GetResolution().y, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    
    FontAtlas atlas = TextMgr::GetInst()->GetFontAtlas(CustomFontName[(int)m_Fonttype]);
    Vec2 drawPos = GetUIRenderPos() + m_TextPos;


    float baseline = atlas.maxbearing * m_FontSize;

    for (wchar_t c : m_Text)
    {
        if (c == 32) {
            drawPos.x += 14;
            continue;
        }
        auto it = atlas.glyphs.find(c);
        if (it == atlas.glyphs.end()) continue;

        const GlyphInfo& glyph = it->second;

        float xpos = drawPos.x + glyph.bearing.x;
        float ypos = drawPos.y + baseline - (glyph.bearing.y * m_FontSize);  // baseline Á¤·Ä

        float w = glyph.size.x * m_FontSize;
        float h = glyph.size.y * m_FontSize;

        glBindTexture(GL_TEXTURE_2D, glyph.textureID);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(xpos, ypos);
        glTexCoord2f(1, 0); glVertex2f(xpos + w, ypos);
        glTexCoord2f(1, 1); glVertex2f(xpos + w, ypos + h);
        glTexCoord2f(0, 1); glVertex2f(xpos, ypos + h);
        glEnd();

        drawPos.x += glyph.advance * m_FontSize;
    }
}

void Text::BeginHover()
{
}

void Text::Hover()
{
}

void Text::EndHover()
{
}

void Text::LBtnDown_UI()
{
}

void Text::LBtnRelease_UI()
{
}

void Text::LBtnClicked()
{
}
