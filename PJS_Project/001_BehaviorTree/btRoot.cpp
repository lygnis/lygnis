#include "btRoot.h"

void BT::btRoot::AddChild(btNode* newChild)
{
}

BT::btNode* BT::btRoot::GetChild()
{
	return ChildNode_;
}

void BT::btRoot::Terminate()
{
	ChildNode_->Terminate();
	
}

BT::enStatus BT::btRoot::Tick()
{
	if (ChildNode_ == nullptr)
	{
		return INVAILD;
	}
	else if (ChildNode_->GetStatus() == INVAILD)
	{
		ChildNode_->Initalize();
		ChildNode_->SetStatus(RUNNING);
	}
	SetStatus(ChildNode_->Update());
	ChildNode_->SetStatus(GetStatus());

	if (GetStatus() != RUNNING)
		Terminate();
	return GetStatus();
}
