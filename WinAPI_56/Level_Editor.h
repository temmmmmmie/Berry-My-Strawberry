#pragma once
#include "Level.h"

class TileActor;

class Level_Editor :
    public Level
{
private:
    HMENU       m_hMenu;
    TileActor* m_TileActor;

public:
    TileActor* GetTileActor() { return m_TileActor; }
    
    void SaveTile();
    void LoadTile();

private:
    void CreateEditorUI();


public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void End() override;

public:
    Level_Editor();
    virtual ~Level_Editor();
};

