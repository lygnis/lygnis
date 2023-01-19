#pragma once
#include <Windows.h>
class MWindow
{
public:
	// 윈도우 초기화
	bool Init();
	bool broadcast();
	bool IsRun();
	// 윈도우 종료
	bool Release();

	RECT GetClientRect();
	void SetHWND(HWND hwnd);
	// 이벤트
	virtual void OnCreate() =0;
	virtual void OnUpdate() =0;
	virtual void OnDestroy();
protected:
	HWND _hwnd;
	bool _is_Run;
public:
	MWindow() {}
	~MWindow() {}
};

