#include "btConditiona.h"

BT::btConditiona::btConditiona()
{
	SetNodeType(CONDITION);
}

BT::enStatus BT::btConditiona::Tick()
{
	SetStatus(Update());
	if (GetStatus() == RUNNING)
	{
		// 에러
		assert(false);
	}
	// 이전 ActionNode를 참조하는 필드변수로 만들어 사용
	if (GetStatus() == SUCCESS)
	{
		// 이전에 다른 노드의 값들을 초기화 하기위해서 반드시 들어가는 조건문
		TerminateRunningAction();
	}
	return GetStatus();
}

void BT::btConditiona::TerminateRunningAction()
{
	btNode* btFindRoot = nullptr;
	int errorCount = 0;
	// find root
	btFindRoot = GetParent();
	
	while (btFindRoot != nullptr)
	{
		btFindRoot = btFindRoot->GetParent();
		if (btFindRoot->GetParent() == nullptr)
			break;
	}
	// find RUNNING Action
	if (btFindRoot != nullptr)
	{
		if (btFindRoot->GetStatus() == RUNNING)
		{
			btNode* btRunningAction = FindRunningAction(((btRoot*)btFindRoot)->GetChild());
			if (btRunningAction != nullptr)
			{
				// 만일 Conditiona 과 Runiing Action이 같은 부모를 가졌고 해당부모가 Squence가 아니라면 Terminate호출
				if (GetParent() != btRunningAction->GetParent() || GetParent()->GetNodeType() != SEQUENCE)
					btRunningAction->Terminate();
			}

		}
	}
}

BT::btNode* BT::btConditiona::FindRunningAction(btNode* btChild)
{
	btNode* btRunningAction = nullptr;
	if (btChild != nullptr)
	{
		if (btChild->GetNodeType() == SELECTOR || btChild->GetNodeType() == SEQUENCE)
		{
			for (int i = 0; i < ((btComposite*)btChild)->GetChildCount(); ++i)
			{
				btRunningAction = FindRunningAction(((btComposite*)btChild)->GetChild(i));
				if (btRunningAction != nullptr)
				{
					return btRunningAction;
				}
			}
		}
		if (btChild->GetNodeType() == ACTION && btChild->GetStatus() == RUNNING)
			return btRunningAction;
	}
	return nullptr;
}
