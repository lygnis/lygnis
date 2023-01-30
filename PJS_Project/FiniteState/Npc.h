#pragma once
#include <vector>
#include <iostream>
#include <Windows.h>
#include "StateMachine.h"
// NPC 는 현상태를 저장하고 상태의 개수를 저장한다
class NPCState;

class Npc
{
private:
	DWORD _dwState;
	StateMachine* _pFsm = nullptr;
public:
	// Npc의 현 상태
	NPCState* _currState;
	// 상태 리스트
	std::vector<NPCState*> _actionList;
public:
	void Process();
	void SetTransition(DWORD dwEvent);
public:
	Npc() {}
	Npc(StateMachine* fsm);
	~Npc() {};
};

