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
    // ������ �ε�
    virtual int Load(const wstring& _FilePath) override;


    // ���� ���
    void Play(bool _bLoop = false);

    // ����������� ���
    void PlayToBGM(bool _bLoop = false);

    // ����
    void Stop(bool _bReset = false);

    // ���� ���� (0 ~ 100)
    void SetVolume(float _fVolume);

    // ���� ��� ��ġ (0 ~ 100)
    void SetPosition(float _fPosition); // 0 ~ 100 

    int GetDecibel(float _fVolume);

    bool LoadWaveSound(const wstring& _strPath);


    ASound();
    virtual ~ASound();
};

