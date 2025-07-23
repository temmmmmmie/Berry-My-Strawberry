#pragma once
#include "Actor.h"

class TileRender;

class TileActor :
    public Actor
{
private:
    TileRender*     m_TileRender;

public:
    TileRender* GetTileRender() { return m_TileRender; }


public:
    virtual void Tick() override;
    virtual void Render(HDC _dc) override;

public:
    TileActor();
    virtual ~TileActor();

};

