#pragma once
#include "Actor.h"

class Collider;

class Missile :
    public Actor
{
private:
    Collider* m_Collider; // �̻��� �浹ü
    float       m_Speed;    // �̻��� �ӷ�
    float       m_Angle;    // �̻��� �̵� ����

    Vec2        m_Velocity; // �̻��� �ӵ�(����, ����, ũ��(�ӷ�))

    float       m_RotateSpeed; // Ÿ���� ���ϴ� ���⺤�� ȸ���ӵ�

    Actor* m_Target;       // ����ź�� ���, ���� ���
    ACTOR_TYPE  m_TargetType;   // ����ź�� ������ ��� �׷�
    float       m_DetectRange;  // ���� ����

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

