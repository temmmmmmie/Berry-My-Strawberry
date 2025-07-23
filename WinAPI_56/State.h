#pragma once
#include "Base.h"

#include "StateMachine.h"

class State :
    public Base
{
private:
    StateMachine*   m_Owner;

public:
    StateMachine* GetOwner() { return m_Owner; }
    Actor* GetOwnerActor() { return m_Owner->GetOwner(); }

public:
    virtual void Enter() = 0; // 해당 상태로 진입
    virtual void FinalTick() = 0; // 상태에서 할 일
    virtual void Exit() = 0; // 해당 상태를 벗어날때 

public:
    State();
    virtual ~State();
    friend class StateMachine;
};

