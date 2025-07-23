#pragma once

#define SINGLE(ClassName)	public:\
								static ClassName* GetInst()\
								{\
									static ClassName mgr;\
									return &mgr;\
								}\
							private:\
								ClassName& operator=(const ClassName& _Other) = delete;\
							private:\
								ClassName();\
								ClassName(const ClassName& _Other) = delete;\
								~ClassName();

#define DT TimeMgr::GetInst()->GetDeltaTime()

#define KEY_CHECK(Key, State)	KeyMgr::GetInst()->GetKeyState(Key) == State
#define KEY_TAP(Key)			KEY_CHECK(Key, KEY_STATE::TAP)
#define KEY_PRESSED(Key)		KEY_CHECK(Key, KEY_STATE::PRESSED)
#define KEY_RELEASED(Key)		KEY_CHECK(Key, KEY_STATE::RELEASED)

#define GET(Type, MemName) Type Get##MemName(){return m_##MemName; }
#define SET(Type, MemName) void Set##MemName(Type _Data){m_##MemName = _Data;}
#define GET_SET(Type, MemName) GET(Type, MemName); SET(Type, MemName);
		

#define PI 3.14159265f

