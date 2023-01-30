#include "Npc.h"
#include "NPCState.h"
void Npc::Process()
{
	_currState->Process();
}

void Npc::SetTransition(DWORD dwEvent)
{
	// �̺�Ʈ�� ������ ���¸� �����Ѵ�.
	DWORD dwOutput = _pFsm->GetTransition(_dwState, dwEvent);
	_currState = _actionList[dwOutput];
}

Npc::Npc(StateMachine* fsm)
{
	_pFsm = fsm;
	_actionList.push_back(new StandState(this));
	_actionList.push_back(new MoveState(this));
	// �⺻���´� Stand
	_currState = _actionList[0];
	_dwState = STATE_STAND;
}


