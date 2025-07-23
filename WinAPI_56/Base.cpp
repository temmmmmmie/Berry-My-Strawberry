#include "pch.h"
#include "Base.h"

UINT Base::g_GlobalID = 0;

Base::Base()
	: m_ID(g_GlobalID++)
{
}

Base::~Base()
{
}
