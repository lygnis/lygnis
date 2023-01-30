#pragma once
#include <Windows.h>
class MWindow
{
public:
	
	bool IsRun();
	// ������ ����

	RECT GetClientRect();
	// �̺�Ʈ
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
	// ������ �ʱ�ȭ
	MWindow();
	~MWindow();
};

