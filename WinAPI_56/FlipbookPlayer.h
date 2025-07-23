#pragma once
#include "Component.h"
#include <functional>

class AFlipbook;

class FlipbookPlayer :
    public Component
{
private:
    vector<AFlipbook*>  m_PlayList;     // 재생 목록 Flipbook

    AFlipbook*          m_CurFlipbook;  // 현재 재생중인 Flipbook
    int                 m_SpriteIdx;    // 현재 재생중인 Flipbook 의 재생중인 스프라이트 인덱스
    float               m_FPS;          // 초당 장면전환 수
    float               m_AccTime;      // 시간 누적용 변수

    int                 m_PlayCount;    // 남은 재생횟수
    bool                m_Repeat;       // 무한반복 여부
    bool                m_Finish;       // 1회 재생 끝나는 시점에 true 로 켜짐
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

