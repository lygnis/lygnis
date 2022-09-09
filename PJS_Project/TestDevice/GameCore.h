#pragma once
#include "DxDevice.h"
#include "TWindow.h"

class GameCore
{
public:
	TWindow*			m_pWindow = nullptr;
	DxDevice*			m_pDevice;

private:
	bool				m_bGameRun = true;
public:
	virtual bool Init()		{ return true; };
	virtual bool Frame()	{ return true; };
	virtual bool Render()	{ return true; };
	virtual bool Release()	{ return true; };
	virtual bool Run();
private:
	bool CoreInit();
	bool CoreFrame();
	bool CoreRender();
	bool CoreRelease();
public:
	bool SetWindow(HINSTANCE hInstance, const WCHAR* _prjName, UINT iWidth ,UINT iHeight);
};

