#include "pch.h"
#include "TextMgr.h"
#include "PathMgr.h"
#include "ShaderLoader.h"
#include <fstream>

wstring CustomFontName[3]
{
    L"HeirofLightBold",
    L"HeirofLightRegular"
};
wstring charset =
    L"가나다라마바사아자차카타파하"
    L"거너더러머버서어저처커터퍼허"
    L"고노도로모보소오조초코토포호"
    L"구누두루무부수우주추쿠투푸후"
    L"그느드르므브스으즈츠크트프흐"
    L"기니디리미비시이지치키티피히"
    L"한글사랑행복사람시간이름학교공부"
    L"안녕하세요감사합니다좋아요테스트"
    L"게임개발디버그텍스트출력성공실패"
    L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    L"abcdefghijklmnopqrstuvwxyz"
    L"0123456789:"
    L"갈가마귀삭제해라"
    L"알벤티오이 게임의 주인공!"
    L"평범한까마귀까악까악"
    L"진짜딸기완전딸기"
    L"진짜 까마귀완전 까마귀"
    L"평범한 까마귀까악까악"
    L"리버스 까치깍깍깍깍깍"
    ;

extern wstring charset;

void TextMgr::init()
{
    if (FT_Init_FreeType(&ft)) {
        MessageBox(nullptr, L"프리타입 라이브러리 로딩 실패", L"프리타입 라이브러리 로딩 실패", MB_OK);
        return;
    }
    //폰트로드
    for (size_t i = 0; i < (int)Fonttype::END; i++)
    {
        wstring fontPath = PathMgr::GetInst()->GetContentPath() + L"Fonts\\" + CustomFontName[i] + L".ttf";
        std::ifstream file(fontPath, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            MessageBox(nullptr, L"폰트 파일을 열 수 없습니다", L"폰트 파일을 열 수 없습니다", MB_OK);
            return;
        }

        // Step 2: 크기 구해서 메모리 할당
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<unsigned char> fontBuffer(size);
        file.read(reinterpret_cast<char*>(fontBuffer.data()), size);
        // Step 3: 메모리에서 폰트 로드
        FT_Face face = nullptr;
        FT_Error err = FT_New_Memory_Face(ft, fontBuffer.data(), (FT_Long)fontBuffer.size(), 0, &face);
        if (err != 0) {
            MessageBox(nullptr, L"메모리에 폰트를 로드할 수 없음", L"메모리에 폰트를 로드할 수 없음", MB_OK);
            return;
        }
        FT_Error err2 = FT_Set_Pixel_Sizes(face, 0, 64);

        Temp.fontBuffer = fontBuffer;

        //-----<Cache>----
        std::map<wchar_t, GlyphInfo> TempglyphsMap;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        for (wchar_t c : charset) {
            if (FT_Load_Char(face, c, FT_LOAD_DEFAULT)) {
                wchar_t buffer[255] = {};
                swprintf_s(buffer, 255, L"캐릭터 로드 실패 : %c", c);
                MessageBox(nullptr, buffer, L"캐릭터 로드 실패", MB_OK);
                continue;
            }
            FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
            FT_GlyphSlot g = face->glyph;
            if (g->bitmap.buffer == nullptr || g->bitmap.width == 0 || g->bitmap.rows == 0) {
                continue; // 텍스처 업로드 하지 말고 건너뛰기
            }

            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_ALPHA,
                g->bitmap.width,
                g->bitmap.rows,
                0,
                GL_ALPHA,
                GL_UNSIGNED_BYTE,
                g->bitmap.buffer
            );

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


            GlyphInfo gi = {
                texture,
                Vec2(g->bitmap.width, g->bitmap.rows),
                Vec2(g->bitmap_left, g->bitmap_top),
                static_cast<GLuint>(g->advance.x >> 6)
            };

            TempglyphsMap[c] = gi;
            if (Temp.maxbearing < gi.bearing.y) {
                Temp.maxbearing = gi.bearing.y;
            }
        }

        Temp.glyphs = TempglyphsMap;

        fonts.insert(make_pair(CustomFontName[i], Temp));

        FT_Done_Face(face);
    }

    FT_Done_FreeType(ft);
}

void TextMgr::Cache(FT_Face _loadedfont, const std::wstring& _fontName)
{
    
}

TextMgr::TextMgr()
{
}
TextMgr::~TextMgr()
{
}
