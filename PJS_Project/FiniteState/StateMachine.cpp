#include "StateMachine.h"

void StateMachine::AddTransition(DWORD inState, DWORD dwEvent, DWORD outState)
{
	FiniteState* pState = nullptr;
	auto ret = _StateMachine.find(inState);
	// 상태를 추가할때 중복값이 있는지 확인을 한다.
	if (ret != _StateMachine.end())
	{
		// 추가하려는 상태값이 존재한다
		pState = ret->second;
	}
	else
	{
		// 추가하는 상태값이 없다
		pState = new FiniteState();
		_StateMachine[inState] = pState;
	}
	pState->AddTransition(dwEvent, outState);
}

DWORD StateMachine::GetTransition(DWORD dwState, DWORD dwEvent)
{
	return _StateMachine[dwState]->GetTransition(dwEvent);
}
