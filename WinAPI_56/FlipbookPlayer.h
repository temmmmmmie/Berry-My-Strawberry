#pragma once
#include "Component.h"
#include <functional>

class AFlipbook;

class FlipbookPlayer :
    public Component
{
private:
    vector<AFlipbook*>  m_PlayList;     // ��� ��� Flipbook

    AFlipbook*          m_CurFlipbook;  // ���� ������� Flipbook
    int                 m_SpriteIdx;    // ���� ������� Flipbook �� ������� ��������Ʈ �ε���
    float               m_FPS;          // �ʴ� �����ȯ ��
    float               m_AccTime;      // �ð� ������ ����

    int                 m_PlayCount;    // ���� ���Ƚ��
    bool                m_Repeat;       // ���ѹݺ� ����
    bool                m_Finish;       // 1ȸ ��� ������ ������ true �� ����
    function<void()>   m_OnAnimationFinished;




public:


    int GetSpriteIdx() { return m_SpriteIdx; };
    void SetSpriteIdx(int _Idx) { m_SpriteIdx = _Idx; };

    void AddFlipbook(int _Idx, AFlipbook* _Flipbook);
    void SetCallback(function<void()> _cb) { m_OnAnimationFinished = _cb; }
    void DeleteCallback() { m_OnAnimationFinished = nullptr; }
    void Play(int _Idx, float _FPS, int _PlayCount)
    {
        m_CurFlipbook = m_PlayList[_Idx];
        m_FPS = _FPS;
        m_PlayCount = _PlayCount;

        if (0 == m_PlayCount)
            m_Repeat = true;
        else
            m_Repeat = false;

        m_Finish = false;
    }
    void Stop()
    {
        m_FPS = 0;
    }

public:
    virtual void FinalTick() override;
    void Render(HDC _dc);


public:
    FlipbookPlayer();
    ~FlipbookPlayer();
};

