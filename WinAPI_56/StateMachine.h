#pragma once
#include "Component.h"


class State;

class StateMachine :
    public Component
{
private:
    map<wstring, State*>    m_mapState;
    State*                  m_CurState;

public:
    State* GetCurState() { return m_CurState; }

    void AddState(const wstring& _Key, State* _State);
    void ChangeState(const wstring& _NextStateKey);

public:
    virtual void FinalTick() override;

public:
    StateMachine();
    ~StateMachine();
};

