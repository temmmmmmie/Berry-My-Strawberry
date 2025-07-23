#pragma once
#include "Component.h"
class Animator :
    public Component
{
private:
    list <AnimationStruct> AnimationList;
public:
    void AddAnimation(AnimationStruct _ani) { AnimationList.push_back(_ani); }
    virtual void FinalTick() override;
public:
    Animator();
    virtual ~Animator();
};

