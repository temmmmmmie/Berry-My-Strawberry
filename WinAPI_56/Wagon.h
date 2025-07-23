#pragma once
#include "Actor.h"

class ATexture;
class Collider;
class FlipbookPlayer;
class Wagon :
    public Actor
{
private:
    Collider* m_Collider;
    FlipbookPlayer* m_FlipbookPlayer;

public:
    void StoreStrawberry();

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render(HDC _dc) override;

    virtual void BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
public:
    Wagon();
    virtual ~Wagon();
};