#pragma once
#include "State.h"
class Strawberrry;

class Idle_Rabbit :
    public State
{
private:
    vector <Strawberrry*> m_Strawberries;
    DIR m_Prevdir;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    void ChangeAnim(DIR _dir);

public:
    Idle_Rabbit();
    virtual ~Idle_Rabbit();

};

