#include "pch.h"
#include "StateMachine.h"

#include "State.h"

StateMachine::StateMachine()
	: Component(COMPONENT_TYPE::STATEMACHINE)
	, m_CurState(nullptr)
{
}

StateMachine::~StateMachine()
{
	for (const auto& pair : m_mapState)
	{
		delete pair.second;
	}
}

void StateMachine::FinalTick()
{
	if (nullptr == m_CurState)
		return;

	m_CurState->FinalTick();
}

void StateMachine::AddState(const wstring& _Key, State* _State)
{
	m_mapState.insert(make_pair(_Key, _State));

	_State->m_Owner = this;
}


void StateMachine::ChangeState(const wstring& _NextStateKey)
{
	map<wstring, State*>::iterator iter = m_mapState.find(_NextStateKey);
	assert(iter != m_mapState.end());
	
	// ���� ���¸� �������´�.
	if (nullptr != m_CurState)
	{
		m_CurState->Exit();
	}	

	// ���ο� ���¸� �����ϰ�, �����Ѵ�.
	m_CurState = iter->second;
	m_CurState->Enter();
}
