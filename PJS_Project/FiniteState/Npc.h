#pragma once
#include <vector>
#include <iostream>
#include <Windows.h>
#include "StateMachine.h"
// NPC �� �����¸� �����ϰ� ������ ������ �����Ѵ�
class NPCState;

class Npc
{
private:
	DWORD _dwState;
	StateMachine* _pFsm = nullptr;
public:
	// Npc�� �� ����
	NPCState* _currState;
	// ���� ����Ʈ
	std::vector<NPCState*> _actionList;
public:
	void Process();
	void SetTransition(DWORD dwEvent);
public:
	Npc() {}
	Npc(StateMachine* fsm);
	~Npc() {};
};

