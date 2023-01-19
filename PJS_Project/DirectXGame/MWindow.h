#pragma once
#include <Windows.h>
class MWindow
{
public:
	// ������ �ʱ�ȭ
	bool Init();
	bool broadcast();
	bool IsRun();
	// ������ ����
	bool Release();

	RECT GetClientRect();
	void SetHWND(HWND hwnd);
	// �̺�Ʈ
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

