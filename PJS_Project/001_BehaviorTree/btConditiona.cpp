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
		// ����
		assert(false);
	}
	// ���� ActionNode�� �����ϴ� �ʵ庯���� ����� ���
	if (GetStatus() == SUCCESS)
	{
		// ������ �ٸ� ����� ������ �ʱ�ȭ �ϱ����ؼ� �ݵ�� ���� ���ǹ�
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
				// ���� Conditiona �� Runiing Action�� ���� �θ� ������ �ش�θ� Squence�� �ƴ϶�� Terminateȣ��
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
