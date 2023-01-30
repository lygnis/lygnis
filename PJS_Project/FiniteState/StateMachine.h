#pragma once
#include "FiniteState.h"

class StateMachine
{
private:
	//
	std::map<DWORD, FiniteState*> _StateMachine;
public:
	// � ���°� �ִ��� �߰��� �Ѵ�.
	void AddTransition(DWORD inState, DWORD dwEvent, DWORD outState);
	// 
	DWORD GetTransition(DWORD dwState, DWORD dwEvent);
};


