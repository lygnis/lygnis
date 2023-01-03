#pragma once
#include "btComposite.h"
namespace BT
{
	// Selector Success�� ������ ��� Success ��ȯ
	// ��� �ڽ��� Failure�� Failure ��ȯ
	class btSelector : public btComposite
	{
	public:
		btSelector()
		{
			SetNodeType(SELECTOR);
		}
		virtual ~btSelector() {}
	public:
		virtual enStatus Update()override;
	protected:
		// �ڽ��� Success or Running�� �߰��ϸ� ��� �ڽ��� �ʱ�ȭ
		void ClearChild(int Index);
	};
}

