#pragma once
#include "DxDevice.h"
#include "Writer.h"
#include "Timer.h"
#include "Input.h"
class GameCore : public DxDevice
{
public:
	Writer				m_wWriter;
	Timer				m_tTimer;
	Input				m_iInput;
	float				m_fTemp;
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
	HRESULT CreateDXResource();
	HRESULT DeleteDXResource();
};

