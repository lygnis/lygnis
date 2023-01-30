#pragma once
#include <Windows.h>
class MWindow
{
public:
	
	bool IsRun();
	// 윈도우 종료

	RECT GetClientRect();
	// 이벤트
	virtual void OnCreate() =0;
	virtual void OnUpdate() =0;
	virtual void OnDestroy();
	virtual void OnFocus();
	virtual void OnKillFocus();
protected:
	HWND _hwnd;
	bool _is_Run;
	bool _is_init = false;
private:
	bool broadcast();
public:
	// 윈도우 초기화
	MWindow();
	~MWindow();
};

