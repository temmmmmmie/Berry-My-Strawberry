#include "pch.h"
#include "Animator.h"
#include "TimeMgr.h"

void Animator::FinalTick()
{
	list <AnimationStruct>::iterator iter;
	for (iter = AnimationList.begin(); iter != AnimationList.end();)
	{
		if (iter->Curtime >= iter->Duration)
		{
			iter = AnimationList.erase(iter);
			continue;
		}
		Vec2 vPos = GetOwner()->GetPos();
		switch (iter->Animationtype)
		{
		case Animationtype::MOVE_LEFT:
			GetOwner()->SetPos(vPos + Vec2(- iter->Speed * DT, 0));
			break;
		case Animationtype::MOVE_RIGHT:
			GetOwner()->SetPos(vPos + Vec2(iter->Speed * DT, 0));
			break;
		}
		if (!iter->Repeated) {
			iter->Curtime += DT;
		}
		++iter;
	}
}

Animator::Animator()
	: Component(COMPONENT_TYPE::ANIMATOR)
{

}

Animator::~Animator()
{
}
