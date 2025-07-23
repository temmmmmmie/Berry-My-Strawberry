#pragma once
#include "Actor.h"

class ATexture;
class FlipbookPlayer;
class Collider;
class Strawberrry :
    public Actor
{
private:
    ATexture* m_CurTexture;
    FlipbookPlayer* m_FlipbookPlayer;
    
    ATexture* m_StrawberryTexture[7];
    Collider* m_Collider;

    int m_CurState;
    float m_Eatentime;

public:
    int GetState() { return m_CurState; }

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render(HDC _dc) override;

    virtual void BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;

    void Growth();
    void Growth(int _growth);
    void Seed();
    void Pick();
    void Eaten();
    void Break();

    void ToStage0();

public:
    Strawberrry();
    virtual ~Strawberrry();
};

