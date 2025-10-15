#include "pch.h"
#include "AssetMgr.h"

#include "Engine.h"
#include "PathMgr.h"
#include "ATexture.h"
#include "ASprite.h"
#include "AFlipbook.h"
#include "ASound.h"
#include "AVideo.h"
#include "VideoPlayer.h"

#include "video_reader.h"


AssetMgr::AssetMgr()
{

}

AssetMgr::~AssetMgr()
{
	map<wstring, ATexture*>::iterator iter = m_mapTex.begin();
	for (; iter != m_mapTex.end(); ++iter)
	{
		delete iter->second;
	}
	map<wstring, ASprite*>::iterator Spriteiter = m_mapSprite.begin();
	for (; Spriteiter != m_mapSprite.end(); ++Spriteiter)
	{
		delete Spriteiter->second;

	}
	map<wstring, AVideo*>::iterator Videoiter = m_mapVideo.begin();
	for (; Videoiter != m_mapVideo.end(); ++Videoiter)
	{
		delete Videoiter->second;
	}
	map<wstring, AFlipbook*>::iterator FIter = m_mapFlipbook.begin();
	for (; FIter != m_mapFlipbook.end(); ++FIter)
	{
		delete FIter->second;
	}
	map<wstring, ASound*>::iterator Sounditer = m_mapSound.begin();
	for (; Sounditer != m_mapSound.end(); ++Sounditer)
	{
		delete Sounditer->second;
	}
}

void AssetMgr::Init()
{
	// SoundDevice ����
	{
		if (FAILED(DirectSoundCreate8(NULL, &m_SoundDevice, NULL)))
		{
			MessageBox(NULL, L"���� ����̽� ���� ����", L"SYSTEM ERROR", MB_OK);
			return;
		}

		// ���� �������� ����
		HWND hWnd = Engine::GetInst()->GetMainWinow();
		if (FAILED(m_SoundDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
		{
			MessageBox(NULL, L"���� �Ŵ��� �ʱ�ȭ ����", L"SYSTEM ERROR", MB_OK);
		}
	}
	LoadInitAsset();
	FindSound(L"BGM")->PlayToBGM(true);
}
void AssetMgr::RegisterToBGM(ASound* _BGM)
{
	if (m_BGM != nullptr)
		m_BGM->Stop();

	m_BGM = _BGM;
}

ATexture* AssetMgr::FindTexture(const wstring& _Key)
{
	map<wstring, ATexture*>::iterator iter = m_mapTex.find(_Key);

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return iter->second;
}

ATexture* AssetMgr::LoadTexture(const wstring& _Key, const wstring& _RelativePath)
{
	// �ε��Ϸ��� Ű������ �̹� �ε��� ������ �ִ��� Ȯ��
	ATexture* pNewTex = FindTexture(_Key);
	if (nullptr != pNewTex)
	{
		// �̹� �ε��� ������ ������, �װ��� ��ȯ
		return pNewTex;
	}
		
	// �ؽ��� ���� ���� �� �ε�
	wstring ContentPath = PathMgr::GetInst()->GetContentPath();
	pNewTex = new ATexture;
	if (FAILED(pNewTex->Load(ContentPath + _RelativePath)))
	{		
		// �ε� ���� ��, �޼��� �ڽ� ����ֱ�
		wchar_t buffer[255] = {};
		swprintf_s(buffer, 255, L"�ؽ��� �ε� ���� : %s", _RelativePath.c_str());

		MessageBox(nullptr, buffer, L"���ҽ� �ε� ����", MB_OK);
		
		delete pNewTex;
		return nullptr;
	}

	// ���� �������� ������ ���(Key, RelativePath)
	pNewTex->SetKey(_Key);
	pNewTex->SetRelativePath(_RelativePath);

	// AssetMgr �� ���� ���
	m_mapTex.insert(make_pair(_Key, pNewTex));

	// ������ ���� ��ȯ
	return pNewTex;
}

AVideo* AssetMgr::FindVideo(const wstring& _Key)
{
	map<wstring, AVideo*>::iterator iter = m_mapVideo.find(_Key);

	if (iter == m_mapVideo.end())
	{
		return nullptr;
	}

	return iter->second;
}

AVideo* AssetMgr::LoadVideo(const wstring& _Key, const wstring& _RelativePathWOExtension, const wstring& _vidformet)
{
	// �ε��Ϸ��� Ű������ �̹� �ε��� ������ �ִ��� Ȯ��
	AVideo* pVideo = FindVideo(_Key);
	if (nullptr != pVideo)
	{
		// �̹� �ε��� ������ ������, �װ��� ��ȯ
		return pVideo;
	}

	// �ؽ��� ���� ���� �� �ε�
	wstring ContentPath = PathMgr::GetInst()->GetContentPath();
	pVideo = new AVideo;
	if (FAILED(pVideo->Load(ContentPath + _RelativePathWOExtension + _vidformet)))
	{
		// �ε� ���� ��, �޼��� �ڽ� ����ֱ�
		wchar_t buffer[255] = {};
		swprintf_s(buffer, 255, L"���� �ε� ���� : %s", _RelativePathWOExtension.c_str());

		MessageBox(nullptr, buffer, L"���ҽ� �ε� ����", MB_OK);

		delete pVideo;
		return nullptr;
	}

	ASound* pSound = new ASound;
	if (FAILED(pSound->Load(ContentPath + _RelativePathWOExtension + L".wav")))
	{
		delete pSound;
		return nullptr;
	}

	// ���� �������� ������ ���(Key, RelativePath)
	pVideo->SetKey(_Key);
	pVideo->SetRelativePath(_RelativePathWOExtension + _vidformet);

	// AssetMgr �� ���� ���
	m_mapVideo.insert(make_pair(_Key, pVideo));

	VideoPlayer::GetInst()->AddVideo(_Key, pVideo);
	VideoPlayer::GetInst()->AddVideoSound(_Key, pSound);
	// ������ ���� ��ȯ
	return pVideo;
}


ASprite* AssetMgr::FindSprite(const wstring& _Key)
{
	map<wstring, ASprite*>::iterator iter = m_mapSprite.find(_Key);

	if (iter == m_mapSprite.end())
	{
		return nullptr;
	}

	return iter->second;
}

ASprite* AssetMgr::LoadSprite(const wstring& _Key, const wstring& _RelativePath)
{
	// �ε��Ϸ��� Ű������ �̹� �ε��� ������ �ִ��� Ȯ��
	ASprite* pSprite = FindSprite(_Key);
	if (nullptr != pSprite)
	{
		// �̹� �ε��� ������ ������, �װ��� ��ȯ
		return pSprite;
	}

	// �ؽ��� ���� ���� �� �ε�
	wstring ContentPath = PathMgr::GetInst()->GetContentPath();
	pSprite = new ASprite;
	if (FAILED(pSprite->Load(ContentPath + _RelativePath)))
	{
		// �ε� ���� ��, �޼��� �ڽ� ����ֱ�
		wchar_t buffer[255] = {};
		swprintf_s(buffer, 255, L"��������Ʈ �ε� ���� : %s", _RelativePath.c_str());

		MessageBox(nullptr, buffer, L"���ҽ� �ε� ����", MB_OK);

		delete pSprite;
		return nullptr;
	}

	// ���� �������� ������ ���(Key, RelativePath)
	pSprite->SetKey(_Key);
	pSprite->SetRelativePath(_RelativePath);

	// AssetMgr �� ���� ���
	m_mapSprite.insert(make_pair(_Key, pSprite));

	// ������ ���� ��ȯ
	return pSprite;
}

int AssetMgr::AddSprite(const wstring& _Key, ASprite* _Sprite)
{
	// �ε��Ϸ��� Ű������ �̹� �ε��� ������ �ִ��� Ȯ��
	ASprite* pSprite = FindSprite(_Key);
	if (nullptr != pSprite)
	{
		return E_FAIL;
	}

	// ���� �������� ������ ���(Key, RelativePath)
	_Sprite->SetKey(_Key);
	
	// AssetMgr �� ���� ���
	m_mapSprite.insert(make_pair(_Key, _Sprite));

	return S_OK;
}

AFlipbook* AssetMgr::FindFlipbook(const wstring& _Key)
{
	map<wstring, AFlipbook*>::iterator iter = m_mapFlipbook.find(_Key);

	if (iter == m_mapFlipbook.end())
	{
		return nullptr;
	}

	return iter->second;
}

AFlipbook* AssetMgr::LoadFlipbook(const wstring& _Key, const wstring& _RelativePath)
{
	// �ε��Ϸ��� Ű������ �̹� �ε��� ������ �ִ��� Ȯ��
	AFlipbook* pFlipbook = FindFlipbook(_Key);
	if (nullptr != pFlipbook)
	{
		// �̹� �ε��� ������ ������, �װ��� ��ȯ
		return pFlipbook;
	}

	// �ؽ��� ���� ���� �� �ε�
	wstring ContentPath = PathMgr::GetInst()->GetContentPath();
	pFlipbook = new AFlipbook;
	if (FAILED(pFlipbook->Load(ContentPath + _RelativePath)))
	{
		// �ε� ���� ��, �޼��� �ڽ� ����ֱ�
		wchar_t buffer[255] = {};
		swprintf_s(buffer, 255, L"��������Ʈ �ε� ���� : %s", _RelativePath.c_str());

		MessageBox(nullptr, buffer, L"���ҽ� �ε� ����", MB_OK);

		delete pFlipbook;
		return nullptr;
	}

	// ���� �������� ������ ���(Key, RelativePath)
	pFlipbook->SetKey(_Key);
	pFlipbook->SetRelativePath(_RelativePath);

	// AssetMgr �� ���� ���
	m_mapFlipbook.insert(make_pair(_Key, pFlipbook));

	// ������ ���� ��ȯ
	return pFlipbook;
}

int AssetMgr::AddFlipbook(const wstring& _Key, AFlipbook* _Sprite)
{
	// �ε��Ϸ��� Ű������ �̹� �ε��� ������ �ִ��� Ȯ��
	AFlipbook* pFlipbook = FindFlipbook(_Key);
	if (nullptr != pFlipbook)
	{
		return E_FAIL;
	}

	// ���� �������� ������ ���(Key, RelativePath)
	_Sprite->SetKey(_Key);

	// AssetMgr �� ���� ���
	m_mapFlipbook.insert(make_pair(_Key, _Sprite));

	return S_OK;
}
ASound* AssetMgr::FindSound(const wstring& _Key)
{
	map<wstring, ASound*>::iterator iter = m_mapSound.find(_Key);

	if (iter == m_mapSound.end())
	{
		return nullptr;
	}

	return iter->second;
}

ASound* AssetMgr::LoadSound(const wstring& _Key, const wstring& _RelativePath)
{
	// �ε��Ϸ��� Ű������ �̹� �ε��� ������ �ִ��� Ȯ��
	ASound* pSound = FindSound(_Key);
	if (nullptr != pSound)
	{
		// �̹� �ε��� ������ ������, �װ��� ��ȯ
		return pSound;
	}

	// �ؽ��� ���� ���� �� �ε�
	wstring ContentPath = PathMgr::GetInst()->GetContentPath();
	pSound = new ASound;
	if (FAILED(pSound->Load(ContentPath + _RelativePath)))
	{
		// �ε� ���� ��, �޼��� �ڽ� ����ֱ�
		wchar_t buffer[255] = {};
		swprintf_s(buffer, 255, L"��������Ʈ �ε� ���� : %s", _RelativePath.c_str());

		MessageBox(nullptr, buffer, L"���ҽ� �ε� ����", MB_OK);

		delete pSound;
		return nullptr;
	}

	// ���� �������� ������ ���(Key, RelativePath)
	pSound->SetKey(_Key);
	pSound->SetRelativePath(_RelativePath);

	// AssetMgr �� ���� ���
	m_mapSound.insert(make_pair(_Key, pSound));

	// ������ ���� ��ȯ
	return pSound;
}


void AssetMgr::CreateSpriteAndFlipbook(ATexture* _Atlas, const wstring& _Key, Vec2 _LeftTop, Vec2 _Slice, int _Count)
{
	wstring SpriteName = _Key;

	// Sprite ����
	ASprite* pSprite = nullptr;
	for (int i = 0; i < _Count; ++i)
	{
		pSprite = new ASprite;
		pSprite->Create(_Atlas, _LeftTop + Vec2(_Slice.x * (float)i, 0.f), _Slice);

		wchar_t buff[256] = {};
		swprintf_s(buff, 256, L"_%d", i);

		AddSprite(SpriteName + buff, pSprite);

		wstring RelativePath = L"Sprite\\";
		RelativePath += SpriteName + buff;
		RelativePath += L".sprite";

		pSprite->SetRelativePath(RelativePath);
		pSprite->Save(PathMgr::GetInst()->GetContentPath() + RelativePath);
	}

	// Flipbook ����
	AFlipbook* pFlipbook = new AFlipbook;

	for (int i = 0; i < _Count; ++i)
	{
		wchar_t buff[256] = {};
		swprintf_s(buff, 256, L"_%d", i);
		SpriteName = _Key + buff;

		pFlipbook->AddSprite(i, FindSprite(SpriteName));
	}

	AddFlipbook(_Key, pFlipbook);

	wstring RelativePath = L"Flipbook\\";
	RelativePath += _Key;
	RelativePath += L".flip";

	pFlipbook->Save(PathMgr::GetInst()->GetContentPath() + RelativePath);
}
void AssetMgr::LoadInitAsset()
{
	LoadVideo(L"MovingCrow", L"Video\\MovingCrow", L".mp4");
	LoadVideo(L"4", L"Video\\4", L".mp4");
	LoadVideo(L"5", L"Video\\5", L".mp4");
	LoadVideo(L"MovingAlbentio", L"Video\\MovingAlbentio", L".mp4");
	// Sprite �� Flipbook ����
	LoadSound(L"BGM", L"Sound\\BGM.wav");
	LoadSound(L"CrowSound", L"Sound\\Crow.wav");
	LoadSound(L"HarvestSound", L"Sound\\Harvest.wav");
	LoadSound(L"StrawberryBreak", L"Sound\\StrawberryBreak.wav");
	LoadSound(L"Sword", L"Sound\\Sword.wav");
	LoadSound(L"Water", L"Sound\\Water.wav");
	LoadSound(L"Seed", L"Sound\\Seed.wav");
	LoadSound(L"Grabbag", L"Sound\\Grabbag.wav");
	LoadSound(L"RabbitEat", L"Sound\\RabbitEat.wav");
	LoadSound(L"RabbitDie", L"Sound\\RabbitDie.wav");

	LoadFlipbook(L"ALBENTIO_WALK_RIGHT", L"Flipbook\\ALBENTIO_WALK_RIGHT.flip");
	LoadFlipbook(L"ALBENTIO_WALK_LEFT", L"Flipbook\\ALBENTIO_WALK_LEFT.flip");
	LoadFlipbook(L"ALBENTIO_WALK_DOWN", L"Flipbook\\ALBENTIO_WALK_DOWN.flip");
	LoadFlipbook(L"ALBENTIO_UP", L"Flipbook\\ALBENTIO_UP.flip");

	LoadFlipbook(L"ALBENTIO_IDLERIGHT", L"Flipbook\\ALBENTIO_IDLERIGHT.flip");
	LoadFlipbook(L"ALBENTIO_IDLELEFT", L"Flipbook\\ALBENTIO_IDLELEFT.flip");
	LoadFlipbook(L"ALBENTIO_IDLEDOWN", L"Flipbook\\ALBENTIO_IDLEDOWN.flip");
	LoadFlipbook(L"ALBENTIO_IDLEUP", L"Flipbook\\ALBENTIO_IDLEUP.flip");

	LoadFlipbook(L"ALBENTIO_BERRY_WALK_RIGHT", L"Flipbook\\ALBENTIO_BERRY_WALK_RIGHT.flip");
	LoadFlipbook(L"ALBENTIO_BERRY_WALK_LEFT", L"Flipbook\\ALBENTIO_BERRY_WALK_LEFT.flip");
	LoadFlipbook(L"ALBENTIO_BERRY_WALK_DOWN", L"Flipbook\\ALBENTIO_BERRY_WALK_DOWN.flip");

	LoadFlipbook(L"ALBENTIO_BERRYRIGHT", L"Flipbook\\ALBENTIO_BERRYRIGHT.flip");
	LoadFlipbook(L"ALBENTIO_BERRYLEFT", L"Flipbook\\ALBENTIO_BERRYLEFT.flip");
	LoadFlipbook(L"ALBENTIO_BERRYDOWN", L"Flipbook\\ALBENTIO_BERRYDOWN.flip");

	LoadFlipbook(L"ALBENTIO_POTION_WALK_RIGHT", L"Flipbook\\ALBENTIO_POTION_WALK_RIGHT.flip");
	LoadFlipbook(L"ALBENTIO_POTION_WALK_LEFT", L"Flipbook\\ALBENTIO_POTION_WALK_LEFT.flip");
	LoadFlipbook(L"ALBENTIO_POTION_WALK_DOWN", L"Flipbook\\ALBENTIO_POTION_WALK_DOWN.flip");

	LoadFlipbook(L"ALBENTIO_POTIONRIGHT", L"Flipbook\\ALBENTIO_POTIONRIGHT.flip");
	LoadFlipbook(L"ALBENTIO_POTIONLEFT", L"Flipbook\\ALBENTIO_POTIONLEFT.flip");
	LoadFlipbook(L"ALBENTIO_POTIONDOWN", L"Flipbook\\ALBENTIO_POTIONDOWN.flip");

	LoadFlipbook(L"ALBENTIO_SEED_WALK_RIGHT", L"Flipbook\\ALBENTIO_SEED_WALK_RIGHT.flip");
	LoadFlipbook(L"ALBENTIO_SEED_WALK_LEFT", L"Flipbook\\ALBENTIO_SEED_WALK_LEFT.flip");
	LoadFlipbook(L"ALBENTIO_SEED_WALK_DOWN", L"Flipbook\\ALBENTIO_SEED_WALK_DOWN.flip");

	LoadFlipbook(L"ALBENTIO_SEEDRIGHT", L"Flipbook\\ALBENTIO_SEEDRIGHT.flip");
	LoadFlipbook(L"ALBENTIO_SEEDLEFT", L"Flipbook\\ALBENTIO_SEEDLEFT.flip");
	LoadFlipbook(L"ALBENTIO_SEEDDOWN", L"Flipbook\\ALBENTIO_SEEDDOWN.flip");

	LoadFlipbook(L"ALBENTIO_SWORD_WALK_RIGHT", L"Flipbook\\ALBENTIO_SWORD_WALK_RIGHT.flip");
	LoadFlipbook(L"ALBENTIO_SWORD_WALK_LEFT", L"Flipbook\\ALBENTIO_SWORD_WALK_LEFT.flip");
	LoadFlipbook(L"ALBENTIO_SWORD_WALK_DOWN", L"Flipbook\\ALBENTIO_SWORD_WALK_DOWN.flip");
	LoadFlipbook(L"ALBENTIO_SWORD_WALK_UP", L"Flipbook\\ALBENTIO_SWORD_WALK_UP.flip");

	LoadFlipbook(L"ALBENTIO_SWORDRIGHT", L"Flipbook\\ALBENTIO_SWORDRIGHT.flip");
	LoadFlipbook(L"ALBENTIO_SWORDLEFT", L"Flipbook\\ALBENTIO_SWORDLEFT.flip");
	LoadFlipbook(L"ALBENTIO_SWORDDOWN", L"Flipbook\\ALBENTIO_SWORDDOWN.flip");
	LoadFlipbook(L"ALBENTIO_SWORDUP", L"Flipbook\\ALBENTIO_SWORDUP.flip");

	LoadFlipbook(L"ALBENTIO_WATER_WALK_RIGHT", L"Flipbook\\ALBENTIO_WATER_WALK_RIGHT.flip");
	LoadFlipbook(L"ALBENTIO_WATER_WALK_LEFT", L"Flipbook\\ALBENTIO_WATER_WALK_LEFT.flip");
	LoadFlipbook(L"ALBENTIO_WATER_WALK_DOWN", L"Flipbook\\ALBENTIO_WATER_WALK_DOWN.flip");

	LoadFlipbook(L"ALBENTIO_WATERRIGHT", L"Flipbook\\ALBENTIO_WATERRIGHT.flip");
	LoadFlipbook(L"ALBENTIO_WATERLEFT", L"Flipbook\\ALBENTIO_WATERLEFT.flip");
	LoadFlipbook(L"ALBENTIO_WATERDOWN", L"Flipbook\\ALBENTIO_WATERDOWN.flip");

	LoadFlipbook(L"ALBENTIO_ATTACK_RIGHT", L"Flipbook\\ALBENTIO_ATTACK_RIGHT.flip");
	LoadFlipbook(L"ALBENTIO_ATTACK_LEFT", L"Flipbook\\ALBENTIO_ATTACK_LEFT.flip");
	LoadFlipbook(L"ALBENTIO_ATTACK_DOWN", L"Flipbook\\ALBENTIO_ATTACK_DOWN.flip");
	LoadFlipbook(L"ALBENTIO_ATTACK_UP", L"Flipbook\\ALBENTIO_ATTACK_UP.flip");

	LoadFlipbook(L"STRAWBERRY5", L"Flipbook\\STRAWBERRY5.flip");
	LoadFlipbook(L"STRAWBERRY_PICK", L"Flipbook\\STRAWBERRY_PICK.flip");
	LoadFlipbook(L"STRAWBERRY_BROKEN", L"Flipbook\\STRAWBERRY_BROKEN.flip");
	LoadFlipbook(L"STRAWBERRY_EATEN", L"Flipbook\\STRAWBERRY_EATEN.flip");

	LoadFlipbook(L"RABBIT_IDLERIGHT", L"Flipbook\\RABBIT_IDLERIGHT.flip");
	LoadFlipbook(L"RABBIT_IDLELEFT", L"Flipbook\\RABBIT_IDLELEFT.flip");
	LoadFlipbook(L"RABBIT_MOVERIGHT", L"Flipbook\\RABBIT_MOVERIGHT.flip");
	LoadFlipbook(L"RABBIT_MOVELEFT", L"Flipbook\\RABBIT_MOVELEFT.flip");
	LoadFlipbook(L"RABBIT_DIELEFT", L"Flipbook\\RABBIT_DIELEFT.flip");
	LoadFlipbook(L"RABBIT_DIERIGHT", L"Flipbook\\RABBIT_DIERIGHT.flip");
	LoadFlipbook(L"RABBIT_ATTACK", L"Flipbook\\RABBIT_ATTACK.flip");

	LoadFlipbook(L"WAGON", L"Flipbook\\WAGON.flip");
}

