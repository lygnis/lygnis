#pragma once
#include "DX3D/Math/Rect.h"
#include "MStd.h"

class MWindow
{
public:
	// 윈도우 종료

	TMath::Rect GetClientSize();
	TMath::Rect GetScreenSize();
	// 이벤트
	//virtual void OnCreate();
	//virtual void OnUpdate();
	virtual void OnDestroy();
	virtual void OnFocus();
	virtual void OnKillFocus();
	virtual void OnSize();
protected:
	TMath::Rect size_ = {0,0,1024,768};
	void* _hwnd;
public:
	// 윈도우 초기화
	MWindow();
	virtual ~MWindow();
};

