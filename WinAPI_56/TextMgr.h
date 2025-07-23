#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include <unordered_map>
#include <GL/glew.h>
#include <gl/GL.h>
class Text;
struct GlyphInfo {
	GLuint textureID;    // �۸��� �ؽ�ó ID
	Vec2 size;     // �۸��� ũ�� (width, height)
	Vec2 bearing;  // �»�� ���� ��� (offset)
	GLuint advance;      // ���� �۸������� �̵� �Ÿ� (�ȼ� ���� << 6 �Ǿ� ����)
};
struct FontAtlas {
	std::vector<unsigned char> fontBuffer;
	std::map<wchar_t, GlyphInfo> glyphs;
	float maxbearing;
};

class TextMgr
{
	SINGLE(TextMgr);
private:
	FT_Library ft;
	std::unordered_map<std::wstring, FontAtlas> fonts;
	FontAtlas Temp;

public:
	void init();
	void Cache(FT_Face _loadedfont, const std::wstring& fontName);
	FontAtlas GetFontAtlas(const wstring _fontname) { return fonts[_fontname]; }
};

