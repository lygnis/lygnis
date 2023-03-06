#pragma once
#include "DX3D/Math/Rect.h"
#include "MStd.h"

class MWindow
{
public:
	// ������ ����

	TMath::Rect GetClientSize();
	TMath::Rect GetScreenSize();
	// �̺�Ʈ
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
	// ������ �ʱ�ȭ
	MWindow();
	virtual ~MWindow();
};

