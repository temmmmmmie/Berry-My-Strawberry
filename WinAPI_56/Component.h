#pragma once

#include "Base.h"
#include "Actor.h"


class Component
	: public Base
{
private:
	// RTTI (RunTime Type Identification(Information) )
	// C++ RTTI - dynamic_cast
	const COMPONENT_TYPE m_Type;
	Actor*				 m_Owner;

public:
	Actor* GetOwner() { return m_Owner; }
	COMPONENT_TYPE GetType() { return m_Type; }

public:
	virtual void FinalTick() = 0;

public:
	Component(COMPONENT_TYPE _Type);
	virtual ~Component();

	friend class Actor;
};

