#pragma once
#include "Actor.h"

class SpriteRender;
class Level_FlipbookEditor;

class SpriteActor : 
	public Actor
{
private:

    SpriteRender* m_SpriteRender;

public:
    SpriteRender* GetSpriteRender() { return m_SpriteRender; }


public:
    virtual void Tick() override;
    virtual void Render(HDC _dc) override;
public:
    SpriteActor(Level_FlipbookEditor* _Curleve);
    ~SpriteActor();

};

