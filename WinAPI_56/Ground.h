#pragma once
#include "Actor.h"
class Ground :
    public Actor
{
private:
    class Collider* m_Collider;


public:
    virtual void Tick() override;
    virtual void Render(HDC _dc) override;

    virtual void BeginOverlap(class Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;

public:
    Ground();
    virtual ~Ground();
};

