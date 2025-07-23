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
    virtual void Enter() = 0; // �ش� ���·� ����
    virtual void FinalTick() = 0; // ���¿��� �� ��
    virtual void Exit() = 0; // �ش� ���¸� ����� 

public:
    State();
    virtual ~State();
    friend class StateMachine;
};

