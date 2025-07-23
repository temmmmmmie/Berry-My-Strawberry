#pragma once
#include "Actor.h"

class ATexture;
class Collider;
class Animator;
class Object :
    public Actor
{
private:
    ATexture* m_Texture;
    Collider* m_Collider;
    Animator* m_Animator;

    bool m_HasCollider;

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render(HDC _dc) override;

    virtual void BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
public:
    Object(ATexture* _tex, bool _hascollider, Vec2 _scale = Vec2( 0, 0), Vec2 _offset = Vec2(0, 0), AnimationStruct* _animation = nullptr);
    virtual ~Object();
};