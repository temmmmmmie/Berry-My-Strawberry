#pragma once
#include "Actor.h"

class Collider;
class Player;

class HitBox :
    public Actor
{
private:
    Collider* m_Collider;
    Player* m_Player;

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render(HDC _dc) override;

    virtual void BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    
    void CrowCall();
public:
    HitBox(Player* _owner);
    virtual ~HitBox();

};

