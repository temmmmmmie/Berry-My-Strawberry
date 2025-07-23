#pragma once
#include "State.h"
class Attack_Player:
	public State
{
private:
    void ToIdle();
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    Attack_Player();
    virtual ~Attack_Player();
};

