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
    L"�����ٶ󸶹ٻ������īŸ����"
    L"�ųʴ����ӹ�������óĿ������"
    L"��뵵�θ𺸼ҿ�����������ȣ"
    L"�����η繫�μ�����������Ǫ��"
    L"�״��帣�Ǻ꽺������ũƮ����"
    L"��ϵ𸮹̺������ġŰƼ����"
    L"�ѱۻ���ູ����ð��̸��б�����"
    L"�ȳ��ϼ��䰨���մϴ����ƿ��׽�Ʈ"
    L"���Ӱ��ߵ�����ؽ�Ʈ��¼�������"
    L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    L"abcdefghijklmnopqrstuvwxyz"
    L"0123456789:"
    L"�������ͻ����ض�"
    L"�˺�Ƽ���� ������ ���ΰ�!"
    L"����ѱ�ͱ�Ǳ��"
    L"��¥�����������"
    L"��¥ ��Ϳ��� ���"
    L"����� ��ͱ�Ǳ��"
    L"������ ��ġ������"
    ;

extern wstring charset;

void TextMgr::init()
{
    if (FT_Init_FreeType(&ft)) {
        MessageBox(nullptr, L"����Ÿ�� ���̺귯�� �ε� ����", L"����Ÿ�� ���̺귯�� �ε� ����", MB_OK);
        return;
    }
    //��Ʈ�ε�
    for (size_t i = 0; i < (int)Fonttype::END; i++)
    {
        wstring fontPath = PathMgr::GetInst()->GetContentPath() + L"Fonts\\" + CustomFontName[i] + L".ttf";
        std::ifstream file(fontPath, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            MessageBox(nullptr, L"��Ʈ ������ �� �� �����ϴ�", L"��Ʈ ������ �� �� �����ϴ�", MB_OK);
            return;
        }

        // Step 2: ũ�� ���ؼ� �޸� �Ҵ�
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<unsigned char> fontBuffer(size);
        file.read(reinterpret_cast<char*>(fontBuffer.data()), size);
        // Step 3: �޸𸮿��� ��Ʈ �ε�
        FT_Face face = nullptr;
        FT_Error err = FT_New_Memory_Face(ft, fontBuffer.data(), (FT_Long)fontBuffer.size(), 0, &face);
        if (err != 0) {
            MessageBox(nullptr, L"�޸𸮿� ��Ʈ�� �ε��� �� ����", L"�޸𸮿� ��Ʈ�� �ε��� �� ����", MB_OK);
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
                swprintf_s(buffer, 255, L"ĳ���� �ε� ���� : %c", c);
                MessageBox(nullptr, buffer, L"ĳ���� �ε� ����", MB_OK);
                continue;
            }
            FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
            FT_GlyphSlot g = face->glyph;
            if (g->bitmap.buffer == nullptr || g->bitmap.width == 0 || g->bitmap.rows == 0) {
                continue; // �ؽ�ó ���ε� ���� ���� �ǳʶٱ�
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
