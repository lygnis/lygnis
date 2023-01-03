#pragma once
#include "btRoot.h"
namespace BT
{
	class btComposite : public btNode
	{
	protected:
		std::vector<btNode*> listChild_;
	public:
		btComposite()
		{
			listChild_.reserve(sizeof(btNode));
		}
		virtual ~btComposite() {};
	public:
		// �ε��� �˻�
		btNode* GetChild(int index);
		int GetChildCount();
		void AddChild(btNode* newChild);
	public:
		virtual void Reset()override;
	};
}

