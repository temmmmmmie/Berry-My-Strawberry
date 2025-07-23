#pragma once
#include "Component.h"

class Collider :
    public Component
{
private:
    Vec2    m_OffsetPos;    // 소유자(Actor) 로부터 떨어진 거리(상대적)
    Vec2    m_Scale;
    Vec2    m_FinalPos;     // 소유자(Actor) Position + m_OffsetPos ==> 충돌체의 실제 위치

    int     m_OverlapCount;
    Vec2    m_Penetratedvec;


public:
    bool    m_Istrigger;
    bool    m_Enabled;

    void SetOffset(Vec2 _Offset){ m_OffsetPos = _Offset; }
    Vec2 GetOffset() { return m_OffsetPos; }

    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
    Vec2 GetScale() { return m_Scale; }

    Vec2 GetFinalPos() { return m_FinalPos; }

    Vec2 GetPenetratedVec() { return m_Penetratedvec; }
    void SetPenetratedVec(Vec2& _vec) { m_Penetratedvec = _vec; }
public:
    void BeginOverlap(Collider* _Other);
    void Overlap(Collider* _Other);
    void EndOverlap(Collider* _Other);

public:
    virtual void FinalTick() override;

public:
    Collider();
    ~Collider();
};

