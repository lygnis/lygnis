#pragma once
#include "DxDevice.h"
#include "TWindow.h"
//#include "BaseObject.h"
#include "Timer.h"
#include "KeyInput.h"
#include "Writer.h"
#include "DynamicObj.h"
class GameCore
{
public:
	IDXGISurface1* m_pBackBuffer;
public:
	TWindow*			m_pWindow = nullptr;
	DxDevice*			m_pDevice;
	BaseObject*			m_pObject;
	Timer				m_tTimer;
	KeyInput			m_tKeyInput;
	Writer				m_wWrite;
	BaseObject*			m_pMap;
	DynamicObj*			m_pUser;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

