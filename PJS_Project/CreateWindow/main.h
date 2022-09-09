#pragma once
#include "MyWindow.h"
class main : public MyWindow
{
public:
	bool Init();			// 초기화	
	bool Frame();			// 실시간 계산
	bool Render();		// 렌더링
	bool Realese();		// 소멸 및 삭제
};

