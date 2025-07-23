#pragma once
#include "Component.h"

enum RIGIDBODY_TYPE
{
    PLATFORMER,
    TOPVIEW,
};

class RigidBody :
    public Component
{
private:
    Vec2            m_Force;    // ������ ��
    Vec2            m_Velocity; // �ӵ�
    float           m_FricCoef; // �������(�ӵ��� �ݴ�������� ����Ǵ� �������)
    float           m_Mass;
    float           m_MaxSpeed; // �̵��� �ִ�ӵ�

    float           m_Gravity;          // �߷°��ӵ�
    float           m_MaxGravitySpeed;  // �߷����� ���ؼ� �߻��� �ӵ��� �ִ�ġ
    Vec2            m_GravityVelocity;

    bool            m_Ground;          // ������ ���ִ��� �ƴ���
    float           m_JumpSpeed;
    float           m_AirMoveCoef;     // ���߿��� ������ ���� ���

    int             m_MaxJumpStack;     // �ִ� ���� Ƚ��
    int             m_JumpStack;        // ���� ���� Ƚ��

    RIGIDBODY_TYPE  m_Type;


public:
    GET_SET(float, Mass);
    GET_SET(Vec2, Velocity);
    GET_SET(float, FricCoef);
    GET_SET(float, MaxSpeed);
    GET_SET(float, Gravity);
    GET_SET(float, MaxGravitySpeed);
    GET_SET(RIGIDBODY_TYPE, Type);
    GET_SET(float, JumpSpeed);
    GET_SET(int, MaxJumpStack);

    GET(Vec2, Force);
    void AddForce(Vec2 _Force) { m_Force += _Force; }
    void AddVelocity(Vec2 _Velocity) { m_Velocity += _Velocity; }

    bool IsGround() { return m_Ground; }
    void SetGround(bool _Set)
    {
        m_Ground = _Set;
        if (m_Ground)
        {
            m_JumpStack = 0;
        }
    }

public:
    void Jump();

public:
    virtual void FinalTick() override;

private:
    void Move_TopView();
    void Move_Platformer();



public:
    RigidBody();
    ~RigidBody();
};