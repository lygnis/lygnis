#pragma once
#include <vector>
namespace BT
{
	// ���ϰ�
	enum enStatus
	{
		INVAILD,
		SUCCESS,
		FAILURE,
		RUNNING,
		ABORTED
	};
	// �� ����� ������ �˷��ش�.
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
	// �ֻ�� �θ�Ŭ����
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

