#pragma once
#include "btComposite.h"
namespace BT
{
	// LefNode
	// RUNNING�� ���������ʴ´�. SUCCESS or FAIURE �� ��ȯ
	// ���Ǹ� üũ�ϴ� ���
	// ��������忡�� ���� ó�� ���ϴ� ����̴�.
	class btConditiona : public btNode
	{
	public:
		btConditiona();
		virtual ~btConditiona() {};
	public:
		enStatus Tick()override;
		void TerminateRunningAction();
		btNode* FindRunningAction(btNode* btChild);

	};
}

