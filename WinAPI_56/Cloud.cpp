#include "pch.h"
#include "Cloud.h"

void Cloud::Tick()
{
	if (GetPos().x > 1000)
	{
		SetPos(Vec2(-800, -350));
	}
}

Cloud::Cloud(ATexture* _tex, bool _hascollider, Vec2 _scale, Vec2 _offset, AnimationStruct* _animation)
	:Object::Object(_tex, _hascollider, _scale, _offset, _animation)
{
}

Cloud::~Cloud()
{
}
