#pragma once
#include "DxDevice.h"
#include "TWindow.h"
#include "Writer.h"
#include "Timer.h"
#include "Input.h"
class GameCore
{
public:
	TWindow*			m_pWindow = nullptr;
	DxDevice*			m_pDevice;
	Writer				m_wWriter;
	Timer				m_tTimer;
	Input				m_iInput;
private:
	bool				m_bGameRun = true;
	IDXGISurface1*		m_pBackBuffer;
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

