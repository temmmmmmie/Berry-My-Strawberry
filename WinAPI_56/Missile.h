#pragma once
#include "Actor.h"

class Collider;

class Missile :
    public Actor
{
private:
    Collider* m_Collider; // 미사일 충돌체
    float       m_Speed;    // 미사일 속력
    float       m_Angle;    // 미사일 이동 방향

    Vec2        m_Velocity; // 미사일 속도(벡터, 방향, 크기(속력))

    float       m_RotateSpeed; // 타겟을 향하는 방향벡터 회전속도

    Actor* m_Target;       // 유도탄일 경우, 추적 대상
    ACTOR_TYPE  m_TargetType;   // 유도탄이 추적할 대상 그룹
    float       m_DetectRange;  // 감지 범위

    float       m_Age;
    float       m_Life;

    class RigidBody* m_Rigid;
public:
    GET_SET(Vec2, Velocity);
    GET_SET(ACTOR_TYPE, TargetType);

private:
    void Move_Angle();
    void Move_DirVector();
    void Move_GuidedMissile();
    void Move_RigidBody();
    void FindTarget();


public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render(HDC _dc) override;
    virtual void BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
public:
    Missile();
    virtual ~Missile();
};

