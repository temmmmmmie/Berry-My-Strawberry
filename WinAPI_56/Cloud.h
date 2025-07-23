#pragma once
#include <Object.h>
class Cloud:
	public Object
{
public:
	virtual void Tick() override;
	Cloud(ATexture* _tex, bool _hascollider, Vec2 _scale = Vec2(0, 0), Vec2 _offset = Vec2(0, 0), AnimationStruct* _animation = nullptr);
	virtual ~Cloud();
};

