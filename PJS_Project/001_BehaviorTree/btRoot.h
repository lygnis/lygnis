#pragma once
#include "Node.h"
namespace BT
{
	class btRoot : public btNode
	{
	private:
		btNode* ChildNode_;
	public:
		btRoot()
		{
			SetNodeType(ROOT);
			SetParent(nullptr);
		}
		virtual ~btRoot() {};
	public:
		void AddChild(btNode* newChild);
		btNode* GetChild();
		virtual void Terminate()override;
		virtual enStatus Tick()override;
	};
}

