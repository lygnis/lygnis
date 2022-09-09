#include "GameCore.h"

bool GameCore::CoreInit()
{
	//m_pWindow = new TWindow;
	m_pDevice = new DxDevice;

	m_pDevice->Init();
	return Init();
}

bool GameCore::CoreFrame()
{
	return Frame();
}
bool GameCore::CoreRender()
{
	m_pDevice->PreRender();
	Render();
	m_pDevice->PostRender();
	return true;
}
bool GameCore::CoreRelease()
{
	Release();
	m_pDevice->Release();

	delete m_pDevice;
	delete m_pWindow;
	return true;
}
bool GameCore::SetWindow(HINSTANCE hInstance, const WCHAR* _prjName, UINT iWidth, UINT iHeight)
{
	m_pWindow = new TWindow;
	m_bGameRun = m_pWindow->SetWindow(hInstance, _prjName, iWidth, iHeight);
	return m_bGameRun;
}
bool GameCore::Run()
{
	CoreInit();
	while (m_bGameRun)
	{
		if (m_pWindow->Run() == true)
		{
			CoreFrame();
			CoreRender();
		}
		else
		{
			return false;
		}
	}
	CoreRelease();
	return true;
}

