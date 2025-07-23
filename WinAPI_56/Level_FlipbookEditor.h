#pragma once
#include "Level.h"

class SpriteActor;
class FlipbookPreview;
class SpriteRender;

enum FlipEditorState
{
    SPRITEEDIT,
    FLIPPREVIEW
};

class Level_FlipbookEditor :
    public Level
{
private:
    FlipEditorState EditorState;

    HMENU       m_hMenu;
    SpriteRender* m_SpriteRender;
    SpriteActor* m_SpriteActor;
    FlipbookPreview* m_FlipbookPreview;

    Vec2 m_RealMouseAnchor;
    Vec2 m_MouseAnchor;

    Vec2 m_MouseScale;
public:
    FlipEditorState GetFlipEditorState() { return EditorState; }
    void SetFlipEditorState(FlipEditorState _state) { EditorState = _state; }

    SpriteActor* GetSpriteActor() { return m_SpriteActor; }
    FlipbookPreview* GetFlipbookPreview() { return m_FlipbookPreview; }

    void DisplayFPS(int FPS);
    void DisplayOffset(Vec2 _offset);
    void SaveFlip();
    void LoadFlip();
public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void End() override;
public:
    Level_FlipbookEditor();
    virtual ~Level_FlipbookEditor();
};

