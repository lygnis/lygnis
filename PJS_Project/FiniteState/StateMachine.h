#pragma once
#include "FiniteState.h"

class StateMachine
{
private:
	//
	std::map<DWORD, FiniteState*> _StateMachine;
public:
	// 어떤 상태가 있는지 추가를 한다.
	void AddTransition(DWORD inState, DWORD dwEvent, DWORD outState);
	// 
	DWORD GetTransition(DWORD dwState, DWORD dwEvent);
};


