#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include <unordered_map>
#include <GL/glew.h>
#include <gl/GL.h>
class Text;
struct GlyphInfo {
	GLuint textureID;    // 글리프 텍스처 ID
	Vec2 size;     // 글리프 크기 (width, height)
	Vec2 bearing;  // 좌상단 기준 베어링 (offset)
	GLuint advance;      // 다음 글리프로의 이동 거리 (픽셀 단위 << 6 되어 있음)
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

