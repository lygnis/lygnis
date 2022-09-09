#pragma once
#include "DxDevice.h"
#include "TWindow.h"
#include "BaseObject.h"
#include "Timer.h"
#include "KeyInput.h"
class GameCore
{
public:
	TWindow*			m_pWindow = nullptr;
	DxDevice*			m_pDevice;
	BaseObject*			m_pObject;
	Timer				m_tTimer;
	KeyInput			m_tKeyInput;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

