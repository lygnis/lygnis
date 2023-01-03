#pragma once
#include "btComposite.h"
namespace BT
{
	// LefNode
	// RUNNING이 존재하지않는다. SUCCESS or FAIURE 을 반환
	// 조건만 체크하는 노드
	// 시퀀스노드에서 제일 처음 접하는 노드이다.
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

