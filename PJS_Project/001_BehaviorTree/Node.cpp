#include "Node.h"

bool BT::btNode::IsTerminated()
{
	return enStatus_ == SUCCESS | enStatus_ == FAILURE;
}

bool BT::btNode::IsRunning()
{
	return enStatus_ == RUNNING;
}

BT::btNode* BT::btNode::GetParent()
{
	return btParent_;
}

BT::enStatus BT::btNode::GetStatus()
{
	return enStatus_;
}

BT::enNodeType BT::btNode::GetNodeType()
{
	return enNodeType_;
}

int BT::btNode::GetIndex()
{
	return Index_;
}

void BT::btNode::SetParent(btNode* btNewParent)
{
	btParent_ = btNewParent;
}


void BT::btNode::SetStatus(enStatus enNewStatus)
{
	enStatus_ = enNewStatus;
}

void BT::btNode::SetNodeType(enNodeType enNewType)
{
	enNodeType_ = enNewType;
}

void BT::btNode::SetIndex(int newIndex)
{
	Index_ = newIndex;
}

void BT::btNode::Reset()
{
	enStatus_ = INVAILD;
}

void BT::btNode::Initalize()
{
	return;
}

BT::enStatus BT::btNode::Update()
{
	return SUCCESS;
}

void BT::btNode::Terminate()
{
}

BT::enStatus BT::btNode::Tick()
{
	if (enStatus_ == INVAILD)
	{
		Initalize();
		enStatus_ = RUNNING;
	}
	enStatus_ = Update();
	if (enStatus_ != RUNNING)
	{
		Terminate();
	}
	return enStatus_;
}
