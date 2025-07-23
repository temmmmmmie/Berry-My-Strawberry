#pragma once
#include "Asset.h"


class ASound :
    public Asset
{
private:
    IDirectSoundBuffer*     m_SoundBuffer;
    DSBUFFERDESC			m_tBuffInfo;
    int						m_iVolume;


public:
    // 파일을 로딩
    virtual int Load(const wstring& _FilePath) override;


    // 사운드 재생
    void Play(bool _bLoop = false);

    // 배경음악으로 재생
    void PlayToBGM(bool _bLoop = false);

    // 정지
    void Stop(bool _bReset = false);

    // 볼륨 설정 (0 ~ 100)
    void SetVolume(float _fVolume);

    // 사운드 재생 위치 (0 ~ 100)
    void SetPosition(float _fPosition); // 0 ~ 100 

    int GetDecibel(float _fVolume);

    bool LoadWaveSound(const wstring& _strPath);


    ASound();
    virtual ~ASound();
};

