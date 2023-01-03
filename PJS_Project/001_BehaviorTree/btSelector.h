#pragma once
#include "btComposite.h"
namespace BT
{
	// Selector Success가 나오는 즉시 Success 반환
	// 모든 자식이 Failure면 Failure 반환
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
		// 자식중 Success or Running을 발견하면 모든 자식을 초기화
		void ClearChild(int Index);
	};
}

