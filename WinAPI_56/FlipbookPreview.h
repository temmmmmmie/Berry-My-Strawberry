#pragma once
#include "Actor.h"

class ATexture;
class AFlipbook;
class FlipbookPlayer;
class Level_FlipbookEditor;

class FlipbookPreview :
    public Actor
{
private:
    Level_FlipbookEditor* Editorlevel;

    FlipbookPlayer* m_FlipbookPlayer;
    AFlipbook* m_Flipbook;

    bool m_StopInfo;

public:
    void SetFlip(AFlipbook* _flip);
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render(HDC _dc) override;

    void Play(int _fps, int _repeatcount);
    void Stop();
    void DisplayInfo();
    void PrevFrame();
    void NextFrame();
    void DeleteFrame();
    void SetOffset(Vec2 _offset);

public:
    FlipbookPreview(Level_FlipbookEditor* _Curlevel, AFlipbook* _flip);
    ~FlipbookPreview();
};

