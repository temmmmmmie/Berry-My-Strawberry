#include "pch.h"
#include "SpriteRender.h"

#include "RenderMgr.h"
#include "AssetMgr.h"
#include "PathMgr.h"
#include "Camera.h"

#include "Level_FlipbookEditor.h"
#include "ATexture.h"
#include "AFlipbook.h"
#include "ASprite.h"


void SpriteRender::SetColRow(UINT _Col, UINT _Row)
{
	if (nullptr == m_Curtex) return;
	float height = (float)m_Curtex->GetHeight() / _Row;
	float width = (float)m_Curtex->GetWidth() / _Col;
	ClearFlip();
	m_Curflip->ResizeVec(_Col * _Row);
	Vec2 Lefttop(0, 0);
	int Count = 0;
	for (size_t i = 0; i < _Row * _Col; i++)
	{
		ASprite* Sprite = new ASprite;
		Sprite->Create(m_Curtex, Lefttop, Vec2(width, height));
		m_Curflip->AddSprite(i, Sprite);
		if (Count == _Col - 1) {
			Lefttop.x = 0;
			Count = 0;
			Lefttop.y += height;
		}
		else
		{
			Lefttop.x += width;
			++Count;
		}
	}
}

void SpriteRender::AddSprite(Vec2 _Lefttop, Vec2 _Slice)
{
	ASprite* Sprite = new ASprite;
	Sprite->Create(m_Curtex, _Lefttop, _Slice);
	m_Curflip->AddSprite(m_Curflip->GetMaxSprite(), Sprite);
}

void SpriteRender::NewFlip(const wstring& _FilePath)
{
	wstring filename = GetFilenameFromPath(_FilePath.c_str());
	wstring relativepath = GetRelativePath(_FilePath.c_str());
	
	m_Curtex = AssetMgr::GetInst()->LoadTexture(filename, relativepath);
	m_Curflip->ResizeVec(0);
	if (nullptr != m_Curtex) {

		m_texresolution = Vec2(m_Curtex->GetWidth(), m_Curtex->GetHeight());
	}
	Camera::GetInst()->SetLook(Vec2(0, 0));
}

void SpriteRender::ClearFlip()
{
	for (size_t i = 0; i < m_Curflip->GetMaxSprite(); i++)
	{
		ASprite* Sprite = m_Curflip->GetSprite(i);
		if (Sprite->GetKey() == L"") {
			delete Sprite;
		}
	}
}


void SpriteRender::Save(const wstring& _FilePath, const wstring& _Filename)
{

	for (int i = 0; i < m_Curflip->GetMaxSprite(); ++i)
	{
		wstring RelativePath = L"Sprite\\";
		wchar_t buff[256] = {};
		swprintf_s(buff, 256, L"_%d", i);
		RelativePath += _Filename + buff;
		RelativePath += L".sprite";

		m_Curflip->GetSprite(i)->SetRelativePath(RelativePath);
		m_Curflip->GetSprite(i)->SetKey(_Filename + buff);
		m_Curflip->GetSprite(i)->Save(PathMgr::GetInst()->GetContentPath() + RelativePath);
	}

	m_Curflip->SetKey(_Filename);
	m_Curflip->SetRelativePath(L"Flipbook\\" + _Filename + L".flip");
	m_Curflip->Save(_FilePath + L".flip");
}

void SpriteRender::Load(const wstring& _FilePath)
{
	m_Curflip->Load(_FilePath);

	m_Curtex = m_Curflip->GetSprite(0)->GetAtlas();
	if (nullptr != m_Curtex) {
		m_texresolution = Vec2(m_Curtex->GetWidth(), m_Curtex->GetHeight());
	}
	Camera::GetInst()->SetLook(Vec2(0, 0));
}

void SpriteRender::FinalTick()
{
	if (m_Curflip->GetMaxSprite() > 0 && nullptr != m_Curtex && m_Level->GetFlipEditorState() == SPRITEEDIT) {

		Vec2 vPos = GetOwner()->GetRenderPos() - m_texresolution / 2;
		for (size_t i = 0; i < m_Curflip->GetMaxSprite(); i++)
		{
			ASprite* sprite = m_Curflip->GetSprite(i);
			Vec2 Spritesize = sprite->GetSlice();
			DrawDebugRect(sprite->GetLeftTop() + Vec2(Spritesize.x /2, Spritesize.y / 2) + vPos, Spritesize, PEN_TYPE::GREEN, 0.f);
		}

	}
}

void SpriteRender::Render(HDC _dc)
{
	Vec2 vActorPos = GetOwner()->GetRenderPos();

	if(m_Curtex && m_Level->GetFlipEditorState() == SPRITEEDIT)
		RenderMgr::GetInst()->Draw(m_Curtex, vActorPos.x, vActorPos.y, m_Curtex->GetWidth(), m_Curtex->GetHeight());
}

SpriteRender::SpriteRender(Level_FlipbookEditor* _Curlevel)
	:m_Level(_Curlevel),
	Component(COMPONENT_TYPE::SPRITERENDER)
{
	m_Curflip = new AFlipbook;
}

SpriteRender::~SpriteRender()
{
	delete m_Curflip;
}
