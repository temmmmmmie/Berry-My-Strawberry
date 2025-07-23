#pragma once
#include "State.h"
class Trace_Rabbit :
    public State
{
private:
    DIR m_Prevdir;
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    void ChangeAnim(DIR _dir);

public:
    Trace_Rabbit();
    virtual ~Trace_Rabbit();
};

