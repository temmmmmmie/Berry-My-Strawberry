#pragma once
#include "Actor.h"


enum PLAYER_ANIM
{
    IDLE_DOWN,
    IDLE_LEFT,
    IDLE_UP,
    IDLE_RIGHT,

    SWORD_DOWN,
    SWORD_LEFT,
    SWORD_UP,
    SWORD_RIGHT,

    WATER_DOWN,
    WATER_LEFT,
    WATER_UP,
    WATER_RIGHT,

    POTION_DOWN,
    POTION_LEFT,
    POTION_UP,
    POTION_RIGHT,

    SEED_DOWN,
    SEED_LEFT,
    SEED_UP,
    SEED_RIGHT,

    BERRY_DOWN,
    BERRY_LEFT,
    BERRY_UP,
    BERRY_RIGHT,

    NONE_MOVE_DOWN,
    NONE_MOVE_LEFT,
    NONE_MOVE_UP,
    NONE_MOVE_RIGHT,
    
    SWORD_MOVE_DOWN,
    SWORD_MOVE_LEFT,
    SWORD_MOVE_UP,
    SWORD_MOVE_RIGHT,

    WATER_MOVE_DOWN,
    WATER_MOVE_LEFT,
    WATER_MOVE_UP,
    WATER_MOVE_RIGHT,

    POTION_MOVE_DOWN,
    POTION_MOVE_LEFT,
    POTION_MOVE_UP,
    POTION_MOVE_RIGHT,

    SEED_MOVE_DOWN,
    SEED_MOVE_LEFT,
    SEED_MOVE_UP,
    SEED_MOVE_RIGHT,

    BERRY_MOVE_DOWN,
    BERRY_MOVE_LEFT,
    BERRY_MOVE_UP,
    BERRY_MOVE_RIGHT,


    ATTACK_DOWN,
    ATTACK_LEFT,
    ATTACK_UP,
    ATTACK_RIGHT,

    POTION_ANIM,
    SEED_ANIM,
    WATER_ANIM,
};

enum PLAYER_STATE
{
    IDLE,
    MOVE,
    ATTACK,
    POTION,
    SEED,
    WATER,
    INTERACT
};


class ATexture;
class ASprite;
class Collider;
class FlipbookPlayer;
class StateMachine;
class RigidBody;

class Player :
    public Actor
{
private:
    ATexture*       m_Image;
    ASprite*        m_Sprite;

    Collider*       m_Collider;
    FlipbookPlayer* m_FlipbookPlayer;
    StateMachine*   m_StateMachine;
    RigidBody*      m_Rigid;

    DIR             m_Dir;
    PLAYER_STATE    m_CurState;
    ITEMS           m_hand;

    int             m_AttackRange;

public:
    DIR GetDir() { return m_Dir; }
    void SetDir(DIR _Dir) { m_Dir = _Dir; }

    void SetState(PLAYER_STATE _State) { m_CurState = _State; }
    PLAYER_STATE GetState() { return m_CurState; }

    ITEMS GetHand() { return m_hand; }
    void SetHand(ITEMS _item) { m_hand = _item; }

    RigidBody* GetRigidBody() { return m_Rigid; }
    int GetAttackRange() { return m_AttackRange; }
public:
    virtual void Tick() override;
    virtual void Render(HDC _dc) override;
    virtual void BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;


public:
    Player();
    virtual ~Player();
};

