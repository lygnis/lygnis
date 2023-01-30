#include "StateMachine.h"

void StateMachine::AddTransition(DWORD inState, DWORD dwEvent, DWORD outState)
{
	FiniteState* pState = nullptr;
	auto ret = _StateMachine.find(inState);
	// ���¸� �߰��Ҷ� �ߺ����� �ִ��� Ȯ���� �Ѵ�.
	if (ret != _StateMachine.end())
	{
		// �߰��Ϸ��� ���°��� �����Ѵ�
		pState = ret->second;
	}
	else
	{
		// �߰��ϴ� ���°��� ����
		pState = new FiniteState();
		_StateMachine[inState] = pState;
	}
	pState->AddTransition(dwEvent, outState);
}

DWORD StateMachine::GetTransition(DWORD dwState, DWORD dwEvent)
{
	return _StateMachine[dwState]->GetTransition(dwEvent);
}
