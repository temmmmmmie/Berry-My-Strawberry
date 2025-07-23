#pragma once
#include "State.h"

class Move_Player :
    public State
{

public:
    void Move();
    void CheckAnim();

private:
    void ChangeFlipbook();


public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    Move_Player();
    virtual ~Move_Player();
};

