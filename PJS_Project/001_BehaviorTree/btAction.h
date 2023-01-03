#pragma once
#include "btComposite.h"
namespace BT
{
	class btAction : public btNode
	{
	public:
		btAction()
		{
			SetNodeType(ACTION);
		}
		virtual ~btAction() {}
	public:
		virtual void Initalize()override {}
		virtual void Terminate()override {}
		virtual void Reset() override;
		virtual enStatus Tick()override;
	};
}

