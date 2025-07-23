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
    Vec2            m_Force;    // 누적된 힘
    Vec2            m_Velocity; // 속도
    float           m_FricCoef; // 마찰계수(속도의 반대방향으로 적용되는 마찰계수)
    float           m_Mass;
    float           m_MaxSpeed; // 이동시 최대속도

    float           m_Gravity;          // 중력가속도
    float           m_MaxGravitySpeed;  // 중력으로 인해서 발생한 속도의 최대치
    Vec2            m_GravityVelocity;

    bool            m_Ground;          // 땅위에 서있는지 아닌지
    float           m_JumpSpeed;
    float           m_AirMoveCoef;     // 공중에서 움직임 제어 계수

    int             m_MaxJumpStack;     // 최대 점프 횟수
    int             m_JumpStack;        // 현재 점프 횟수

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