#pragma once
#include "Level.h"
class Level_Stage01 :
    public Level
{

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void End() override;
    void ClearActor(ACTOR_TYPE _type);

    void SpawnRabbit(int _num);

public:
    Level_Stage01();
    virtual ~Level_Stage01();
};

