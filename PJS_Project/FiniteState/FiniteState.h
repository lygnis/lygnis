#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <Windows.h>
#include <memory>
enum FSMState
{
	STATE_STAND = 0,
	STATE_MOVE,
	STATE_ATTACK,
	STATE_COUNT,
};
enum FSMEvent
{
	EVENT_STOPMOVE = 0,
	EVENT_TIMEMOVE,
	EVENT_POINTMOVE,
	EVENT_FINDTARGET,
	EVENT_LOSTTARGET,
	EVENT_COUNT,
};

class FiniteState
{
public:
	// 이벤트 , 상태
	std::map<DWORD, DWORD> _State;
public:
	void AddTransition(DWORD dwEvent, DWORD outState);
	DWORD GetTransition(DWORD dwEvent);
};

