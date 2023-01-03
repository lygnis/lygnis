#pragma once
#include "btComposite.h"
namespace BT
{
	class btSequence : public btComposite
	{
	public:
		btSequence()
		{
			SetNodeType(SEQUENCE);
		}
		virtual ~btSequence() {}
	public:
		virtual enStatus Update() override;

	};
}

