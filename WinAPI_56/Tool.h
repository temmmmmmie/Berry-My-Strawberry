#pragma once
#include "Actor.h"
#include "Collider.h"

class ATexture;
class Tool :
    public Actor
{
private:
    ATexture* m_Texture;
    Collider* m_Collider;

    tooltype m_Tooltype;
    
    bool m_Enbled;
public:
    void Enable() {
        m_Enbled = true;
        m_Collider->m_Enabled = true;
    };
    void Disable() {
        m_Enbled = false;
        m_Collider->m_Enabled = false;
    };

    tooltype GetTooltype() { return m_Tooltype; }
    void SetTooltype(tooltype _type) { m_Tooltype = _type; }

    Collider* GetCollider() { return m_Collider; }

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render(HDC _dc) override;

    virtual void BeginOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void Overlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
    virtual void EndOverlap(Collider* _OwnCollider, Actor* _OtherActor, Collider* _OtherCollider) override;
public:
    Tool(tooltype type);
    virtual ~Tool();
};