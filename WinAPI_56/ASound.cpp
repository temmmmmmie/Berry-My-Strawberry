#include "pch.h"
#include "ASound.h"

#include "AssetMgr.h"

ASound::ASound()
	: m_SoundBuffer(nullptr)
	, m_tBuffInfo{}
{
}

ASound::~ASound()
{
	if (nullptr != m_SoundBuffer)
		m_SoundBuffer->Release();
}

int ASound::Load(const wstring& _FilePath)
{
	assert(AssetMgr::GetInst()->GetSoundDevice());

	wchar_t szExt[10] = { 0 };
	_wsplitpath_s(_FilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 10);

	if (!wcscmp(szExt, L".wav"))
	{
		if (FAILED(LoadWaveSound(_FilePath)))
			assert(nullptr);
	}
	else
		assert(nullptr);

	return S_OK;
}


bool ASound::LoadWaveSound(const wstring& _strPath)
{
	HMMIO	hFile; // File Handle

	wstring strFilePath = _strPath;

	// CreateFile
	hFile = mmioOpen((wchar_t*)strFilePath.c_str(), NULL, MMIO_READ);// wave 파일 열기

	if (nullptr == hFile)
	{
		return E_FAIL;
	}

	// Chunk, wave 파일 구조 분석
	MMCKINFO	pParent;
	memset(&pParent, 0, sizeof(pParent));
	pParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmioDescend(hFile, &pParent, NULL, MMIO_FINDRIFF);

	MMCKINFO	pChild;
	memset(&pChild, 0, sizeof(pChild));
	pChild.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	WAVEFORMATEX	wft;
	memset(&wft, 0, sizeof(wft));
	mmioRead(hFile, (char*)&wft, sizeof(wft));

	mmioAscend(hFile, &pChild, 0);
	pChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	memset(&m_tBuffInfo, 0, sizeof(DSBUFFERDESC));
	m_tBuffInfo.dwBufferBytes = pChild.cksize;
	m_tBuffInfo.dwSize = sizeof(DSBUFFERDESC);
	m_tBuffInfo.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLVOLUME;
	m_tBuffInfo.lpwfxFormat = &wft;

	if (FAILED(AssetMgr::GetInst()->GetSoundDevice()->CreateSoundBuffer(&m_tBuffInfo, &m_SoundBuffer, NULL)))
	{
		MessageBox(NULL, L"웨이브 파일 로딩 실패", L"에러", MB_OK);
		return E_FAIL;
	}

	void* pWrite1 = NULL;
	void* pWrite2 = NULL;
	DWORD dwlength1, dwlength2;

	m_SoundBuffer->Lock(0, pChild.cksize, &pWrite1, &dwlength1
		, &pWrite2, &dwlength2, 0L);

	if (pWrite1 != nullptr)
		mmioRead(hFile, (char*)pWrite1, dwlength1);
	if (pWrite2 != nullptr)
		mmioRead(hFile, (char*)pWrite2, dwlength2);

	m_SoundBuffer->Unlock(pWrite1, dwlength1, pWrite2, dwlength2);

	mmioClose(hFile, 0);

	// 기본 볼륨 50으로 설정
	SetVolume(50.f);

	return true;
}


void ASound::Play(bool _bLoop)
{
	m_SoundBuffer->SetCurrentPosition(0);

	if (_bLoop)
		m_SoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	else
		m_SoundBuffer->Play(0, 0, 0);
}

void ASound::PlayToBGM(bool _bLoop)
{
	AssetMgr::GetInst()->RegisterToBGM(this);

	m_SoundBuffer->SetCurrentPosition(0);

	if (_bLoop)
		m_SoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	else
		m_SoundBuffer->Play(0, 0, 0);
}

void ASound::Stop(bool _bReset)
{
	m_SoundBuffer->Stop();

	if (_bReset)
		m_SoundBuffer->SetCurrentPosition(0);
}


void ASound::SetVolume(float _fVolume)
{
	m_iVolume = GetDecibel(_fVolume);
	m_SoundBuffer->SetVolume(m_iVolume);
}

void ASound::SetPosition(float _fPosition)
{
	Stop(true);

	DWORD dwBytes = (DWORD)((_fPosition / 100.f) * (float)m_tBuffInfo.dwBufferBytes);
	m_SoundBuffer->SetCurrentPosition(dwBytes);
}

int ASound::GetDecibel(float _fVolume)
{
	if (_fVolume > 100.f)
		_fVolume = 100.f;
	else if (_fVolume <= 0.f)
		_fVolume = 0.00001f;

	// 1 ~ 100 의 값을 데시벨로 변환
	int iVolume = (LONG)(-2000.0 * log10(100.f / _fVolume));

	if (iVolume < -10000)
		iVolume = -10000;
	return  iVolume;
}