#pragma once
#include <vector>
namespace BT
{
	// 리턴값
	enum enStatus
	{
		INVAILD,
		SUCCESS,
		FAILURE,
		RUNNING,
		ABORTED
	};
	// 각 노드의 역할을 알려준다.
	enum enNodeType
	{
		ROOT,
		SELECTOR,
		SEQUENCE,
		PARALLER,
		DECORATOT,
		CONDITION,
		ACTION
	};
	// 최상단 부모클래스
	class btNode
	{
	public:
	private:
		enStatus	enStatus_;
		enNodeType	enNodeType_;
		int			Index_;
		btNode*		btParent_;
	public:
		btNode()
		{
			enStatus_ = INVAILD;
		}
		~btNode();

	public:
		bool		IsTerminated();
		bool		IsRunning();
		btNode*		GetParent();
		enStatus	GetStatus();
		enNodeType	GetNodeType();
		int			GetIndex();
		void		SetParent(btNode* btNewParent);
		void		SetStatus(enStatus enNewStatus);
		void		SetNodeType(enNodeType enNewType);
		void		SetIndex(int newIndex);
	public:
		virtual void Reset();
		virtual void Initalize();
		virtual enStatus Update();
		virtual void Terminate();
		virtual enStatus Tick();
	};
}

