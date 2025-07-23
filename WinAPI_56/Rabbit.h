#pragma once
#include "Actor.h"
enum class RABBIT_ANIM
{
    IDLE_LEFT,
    IDLE_RIGHT,

    MOVE_LEFT,
    MOVE_RIGHT,

    DIE_LEFT,
    DIE_RIGHT,

    ATTACK,
};

enum class RABBIT_STATE
{
    IDLE,
    TRACE,
    ATTACK,
    DIE
};
class ATexture;
class Collider;
class FlipbookPlayer;
class StateMachine;
class RigidBody;
class Strawberrry;

class Rabbit :
    public Actor
{
private:

    Collider* m_Collider;
    FlipbookPlayer* m_FlipbookPlayer;
    StateMachine* m_StateMachine;
    RigidBody* m_Rigid;

    DIR             m_Dir;
    RABBIT_STATE    m_CurState;

    int m_MoveRange;
    Vec2 m_Target;
    Strawberrry* m_TargetStrawberry;

    bool Arrived;

public:
    DIR GetDir() { return m_Dir; }
    void SetDir(DIR _Dir) { m_Dir = _Dir; }

    void SetState(RABBIT_STATE _State) { m_CurState = _State; }
    RABBIT_STATE GetState() { return m_CurState; }

    RigidBody* GetRigidBody() { return m_Rigid; }
    int GetMoveRange() { return m_MoveRange; }

    Vec2 Gettarget() { return m_Target; }
    Strawberrry* GetStrawberry() { return m_TargetStrawberry; }
    void Settarget();
    void Settarget(Vec2 _target) { m_Target = _target; }
    void Settarget(Strawberrry* _target) { m_TargetStrawberry = _target; }
    bool GetArrived() { return Arrived; }
    void Move(Vec2 _target);

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render(HDC _dc) override;

    virtual void BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;

    void Die();

public:
    Rabbit();
    virtual ~Rabbit();
};

