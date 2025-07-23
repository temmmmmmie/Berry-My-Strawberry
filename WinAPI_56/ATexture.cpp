#include "pch.h"
#include "ATexture.h"

#include "Engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/gl.h>
ATexture::ATexture()
	: m_hBitmap(0)
{
}

ATexture::~ATexture()
{
}

// wstring 경로를 FILE*로 열기
FILE* _wfopen_s_fallback(const std::wstring& wpath, const wchar_t* mode)
{
	FILE* file = nullptr;
	_wfopen_s(&file, wpath.c_str(), mode);
	return file;
}

int ATexture::Load(const wstring& _FilePath)
{
	if (m_hBitmap != 0)
	{
		glDeleteTextures(1, &m_hBitmap);
		m_hBitmap = 0;
	}
	int w, h, channels;
	FILE* file = _wfopen_s_fallback(_FilePath, L"rb");  // rb = binary read
	if (!file)
		return E_FAIL;

	unsigned char* data = stbi_load_from_file(file, &w, &h, &channels, STBI_rgb_alpha);
	fclose(file);
	if (!data) return E_FAIL;

	m_Width = w;
	m_Height = h;
	glGenTextures(1, &m_hBitmap);
	glBindTexture(GL_TEXTURE_2D, m_hBitmap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
	return S_OK;
}




